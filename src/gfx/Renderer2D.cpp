#include "Phoenix/Log.hpp"
#include "Phoenix/gfx/Api.hpp"
#include "Phoenix/gfx/Texture.hpp"
#include "Phoenix/gfx/ogl/Buffer.hpp"
#include "glm/detail/qualifier.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/mat4x4.hpp"
#include <complex>
#include <cstddef>
#include <cstdint>
#include <Phoenix/gfx/Renderer2D.hpp>
#include <glad/glad.h>

#include <Phoenix/gfx/ogl/OGL.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <memory>
#include <stdio.h>
namespace phnx {
namespace gfx {

static uint32_t vaoID;
static uint32_t vboID;

static uint32_t renderTimeQueryID;
static int32_t renderTimeSum;

#define MAX_QUADS (8192)
#define MAX_TRIS (MAX_QUADS * 2)
#define MAX_INDICES (MAX_TRIS * 3)
#define MAX_VERTS (MAX_QUADS * 4)

#define POSITION_INDEX 0
#define COLOR_INDEX 1
#define TEXCOORD_INDEX 2

static Vertex2D vertices[MAX_VERTS];
static uint16_t indexPtr = 0;
static uint16_t vertexPtr = 0;

static std::shared_ptr<Texture2D> activeAlbedo;

static glm::mat4x4 proj;
static float Width = 1, Height = 1;

static int batches;

static std::unique_ptr<GL::Buffer> sVBO;

void Clear(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void SetFrameSize(float w, float h) {
    Flush();
    proj = glm::ortho(0.0f, w, h, 0.0f);
    glViewport(0, 0, w, h);
    Width = w;
    Height = h;
}

void RotatedQuad(const glm::vec2 &ctr, float angle,const glm::vec2 &size,const glm::vec3 &color, const glm::vec2& uv0, const glm::vec2& uv1) {
    glm::mat4 transform = glm::mat4(1);

    

    
    glm::mat4 rot = glm::rotate(glm::mat4(1), angle, {0, 0, 1});
    glm::mat4 trans = glm::translate(glm::mat4(1), {ctr.x, ctr.y, 0});
    glm::mat4 scale = glm::scale(glm::mat4(1), {size.x, size.y, 1});
    glm::vec4 trp, tlp, brp, blp;
    trp = {+1, +1, 0, 0};
    tlp = {-1, +1, 0, 0};
    blp = {-1, -1, 0, 0};
    brp = {+1, -1, 0, 0};

    trp = trp * trans * proj;
    tlp = tlp * trans * proj;
    brp = brp * trans * proj;
    blp = blp * trans * proj;

    Vertex2D tl, tr, bl, br;

    tr.mPosition.x = trp.x;
    tr.mPosition.y = trp.y;

    tl.mPosition.x = tlp.x;
    tl.mPosition.y = tlp.y;

    br.mPosition.x = brp.x;
    br.mPosition.y = brp.y;

    bl.mPosition.x = blp.x;
    bl.mPosition.y = blp.y;

    tr.mUV = uv1;
    tl.mUV = {uv0.x, uv1.y};
    br.mUV = {uv1.x, uv0.y};
    bl.mUV = uv0;

    tr.mColor = color;
    tl.mColor = color;
    bl.mColor = color;
    br.mColor = color;

    
    
    
    

    vertices[vertexPtr++] = tr;
    vertices[vertexPtr++] = br;
    vertices[vertexPtr++] = bl;
    vertices[vertexPtr++] = tl;

}


void Quad(const glm::vec2 &ctr, const glm::vec2 &size, const glm::vec3 &color,const glm::vec2& uv0, const glm::vec2& uv1) {
    
    Vertex2D tl, tr, bl, br;

    tr.mPosition.x = ctr.x + size.x / 2.0f;
    tr.mPosition.y = ctr.y + size.y / 2.0f;

    tl.mPosition.x = ctr.x - size.x / 2.0f;
    tl.mPosition.y = ctr.y + size.y / 2.0f;

    br.mPosition.x = ctr.x + size.x / 2.0f;
    br.mPosition.y = ctr.y - size.y / 2.0f;

    bl.mPosition.x = ctr.x - size.x / 2.0f;
    bl.mPosition.y = ctr.y - size.y / 2.0f;

    tr.mUV = uv1;
    tl.mUV = {uv0.x, uv1.y};
    br.mUV = {uv1.x, uv0.y};
    bl.mUV = uv0;

    tr.mColor = color;
    tl.mColor = color;
    bl.mColor = color;
    br.mColor = color;

    PushVertex(tr);
    PushVertex(br);
    PushVertex(bl);
    PushVertex(tl);
}

void Init() {

    proj = glm::identity<glm::mat4x4>();
    sVBO = std::make_unique<GL::Buffer>(phnx::gfx::BufferType::VERTEX);
    glGenVertexArrays(1, &vaoID);

    glBindVertexArray(vaoID);
    sVBO->Bind();
    sVBO->SetData<Vertex2D>(nullptr, MAX_VERTS);

    uint32_t stride = sizeof(Vertex2D);

    sVBO->SetLayout(POSITION_INDEX, DataType::F32, 3, stride, offsetof(Vertex2D, mPosition));
    
    sVBO->SetLayout(COLOR_INDEX, DataType::F32, 3, stride, offsetof(Vertex2D, mColor));
    sVBO->SetLayout(TEXCOORD_INDEX, DataType::F32, 3, stride, offsetof(Vertex2D, mUV));

    sVBO->Unbind();

    glGenQueries(1, &renderTimeQueryID);

    printf("Initialized Renderer2D - Vertex2D Size: %d Bytes - %03fMB / Batch\n", stride,
           (float)(stride * MAX_VERTS) / (float)(1 << 20));
}

void Flush() {
    if (vertexPtr == 0) {
        return;
    }

    // printf("Flushing %d Vertices\n", vertexPtr);
    glBindVertexArray(vaoID);

    sVBO->Bind();
    sVBO->SetData(vertices, vertexPtr);
    glBeginQuery(GL_TIME_ELAPSED, renderTimeQueryID);
    glDrawArrays(GL_QUADS, 0, vertexPtr);
    glEndQuery(GL_TIME_ELAPSED);

    sVBO->Unbind();
    glBindVertexArray(0);

    indexPtr = 0;
    vertexPtr = 0;

    batches++;
}

void PushVertex(glm::vec2 pos, glm::vec3 color, glm::vec2 uv) {}

void PushVertex(Vertex2D v) {
    if (vertexPtr >= MAX_VERTS) {
        Flush();
    }

    glm::vec4 pos4 = {v.mPosition.x, v.mPosition.y, 0, 1};

    pos4 = proj * pos4;

    v.mPosition = {pos4.x, pos4.y};

    vertices[vertexPtr++] = v;
}

void SetAlbedo(std::shared_ptr<Texture2D> albedo) {

    if (albedo == nullptr) {
        return;
    }

    if (activeAlbedo == nullptr || activeAlbedo->ID() != albedo->ID()) {
        Flush();
    }

    activeAlbedo = albedo;

    activeAlbedo->SetUnit(0);
}

int BatchCount() { return batches; }

int RenderTime() {
    uint64_t renderTime;
    glGetQueryObjectui64v(renderTimeQueryID, GL_QUERY_RESULT, &renderTime);
    return renderTime;
}

void ResetStats() {
    batches = 0;
    renderTimeSum = 0;
}


float FrameWidthF() {
    return Width;
}

float FrameHeightF() {
    return Height;
}

int FrameWidth() {
    return Width;
}

int FrameHeight() {
    return Height;
}


void TextureRect(std::shared_ptr<Texture2D> texture, const glm::vec2 &ctr, const Rect& rect, const glm::vec2 &size, const glm::vec3 &color) {
    SetAlbedo(texture);
    glm::vec2 p0 = {rect.X, rect.Y};
    glm::vec2 p1 = {rect.X + rect.Width, rect.Y + rect.Height};


    Quad(ctr, size, color, p0 / texture->Size(), p1 / texture->Size());
}


} // namespace gfx
} // namespace phnx
