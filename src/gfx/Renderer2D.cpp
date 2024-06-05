#include "gfx/Texture.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/mat4x4.hpp"
#include <complex>
#include <cstddef>
#include <cstdint>
#include <gfx/Renderer2D.hpp>
#include <glad/glad.h>

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

static uint16_t indices[MAX_INDICES];
static Vertex2D vertices[MAX_VERTS];
static uint16_t indexPtr = 0;
static uint16_t vertexPtr = 0;

static std::shared_ptr<Texture2D> activeAlbedo;

static glm::mat4x4 proj;

static int batches;

void Clear(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void SetFrameSize(float w, float h) {
    Flush();
    proj = glm::ortho(0.0f, w, h, 0.0f);
}

void Quad(glm::vec2 &ctr, glm::vec2 &size, glm::vec3 &color) {
    Vertex2D tl, tr, bl, br;

    tr.mPosition.x = ctr.x + size.x / 2.0f;
    tr.mPosition.y = ctr.y + size.y / 2.0f;

    tl.mPosition.x = ctr.x - size.x / 2.0f;
    tl.mPosition.y = ctr.y + size.y / 2.0f;

    br.mPosition.x = ctr.x + size.x / 2.0f;
    br.mPosition.y = ctr.y - size.y / 2.0f;

    bl.mPosition.x = ctr.x - size.x / 2.0f;
    bl.mPosition.y = ctr.y - size.y / 2.0f;

    tr.mUV = {1.0, 1.0};
    tl.mUV = {0.0, 1.0};
    br.mUV = {1.0, 0.0};
    bl.mUV = {0.0, 0.0};

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

    glGenVertexArrays(1, &vaoID);
    glGenBuffers(1, &vboID);

    glBindVertexArray(vaoID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);

    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2D) * MAX_VERTS, nullptr, GL_STREAM_DRAW);

    uint32_t stride = sizeof(Vertex2D);

    glVertexAttribPointer(POSITION_INDEX, 2, GL_FLOAT, GL_FALSE, stride, (void *)offsetof(Vertex2D, mPosition));

    glVertexAttribPointer(COLOR_INDEX, 3, GL_FLOAT, GL_FALSE, stride, (void *)offsetof(Vertex2D, mColor));

    glVertexAttribPointer(TEXCOORD_INDEX, 2, GL_FLOAT, GL_FALSE, stride, (void *)offsetof(Vertex2D, mUV));

    glEnableVertexAttribArray(POSITION_INDEX);
    glEnableVertexAttribArray(COLOR_INDEX);
    glEnableVertexAttribArray(TEXCOORD_INDEX);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

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

    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex2D) * vertexPtr, vertices);
    glBeginQuery(GL_TIME_ELAPSED, renderTimeQueryID);
    glDrawArrays(GL_QUADS, 0, vertexPtr);
    glEndQuery(GL_TIME_ELAPSED);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
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
    if (activeAlbedo == nullptr || activeAlbedo->ID() != albedo->ID()) {
        Flush();
    }

    activeAlbedo = albedo;

    activeAlbedo->SetUnit(1);
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

} // namespace gfx
} // namespace phnx
