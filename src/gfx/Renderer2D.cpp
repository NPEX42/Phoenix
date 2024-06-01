#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float3.hpp"
#include <cstddef>
#include <cstdint>
#include <gfx/Renderer2D.hpp>
#include <glad/glad.h>
#include <stdio.h>

static uint32_t vaoID;
static uint32_t vboID;

struct Vertex2D {
    glm::vec3 mPosition;
    glm::vec3 mColor;
    glm::vec2 mUV;
};

#define MAX_QUADS (8192)
#define MAX_TRIS (MAX_QUADS * 2)
#define MAX_INDICES (MAX_TRIS * 3)

#define POSITION_INDEX 0
#define COLOR_INDEX 1
#define TEXCOORD_INDEX 2

static uint16_t indices[MAX_INDICES];
static Vertex2D vertices[MAX_QUADS * 4];
static uint16_t indexPtr = 0;
static uint16_t vertexPtr = 0;

void phnx::gfx::Clear(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void phnx::gfx::Quad(float cx, float cy, float w, float y, glm::vec3 &color) {}

void phnx::gfx::Init() {
    glGenVertexArrays(1, &vaoID);
    glGenBuffers(1, &vboID);

    glBindVertexArray(vaoID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);

    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2D) * MAX_QUADS * 4, nullptr,
                 GL_DYNAMIC_DRAW);

    uint32_t stride = sizeof(Vertex2D);

    glVertexAttribPointer(POSITION_INDEX, 3, GL_FLOAT, GL_FALSE, stride,
                          (void *)offsetof(Vertex2D, mPosition));

    glVertexAttribPointer(COLOR_INDEX, 3, GL_FLOAT, GL_FALSE, stride,
                          (void *)offsetof(Vertex2D, mColor));

    glVertexAttribPointer(TEXCOORD_INDEX, 2, GL_FLOAT, GL_FALSE, stride,
                          (void *)offsetof(Vertex2D, mUV));

    glEnableVertexAttribArray(POSITION_INDEX);
    glEnableVertexAttribArray(COLOR_INDEX);
    glEnableVertexAttribArray(TEXCOORD_INDEX);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void phnx::gfx::Flush() {
    // if (indexPtr == 0) {
    //     return;
    // }

    // printf("Flushing %d Vertices\n", vertexPtr);

    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex2D) * vertexPtr, vertices);
    glDrawArrays(GL_TRIANGLES, 0, vertexPtr);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    indexPtr = 0;
    vertexPtr = 0;
}

void phnx::gfx::PushVertex(glm::vec3 pos, glm::vec3 color, glm::vec2 uv) {
    if (vertexPtr == MAX_QUADS * 4) {
        Flush();
    }

    vertices[vertexPtr++] = Vertex2D{
        .mPosition = pos,
        .mColor = color,
        .mUV = uv,
    };
}
