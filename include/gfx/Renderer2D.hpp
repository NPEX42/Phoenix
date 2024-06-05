#pragma once

#include "gfx/Texture.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float3.hpp"
#include <glm/vec3.hpp>

#include <memory>
namespace phnx {
namespace gfx {

struct Vertex2D {
    glm::vec2 mPosition;
    glm::vec3 mColor;
    glm::vec2 mUV;
};

void Clear(float r, float g, float b, float a);
void Quad(glm::vec2 &ctr, glm::vec2 &size, glm::vec3 &color);

void Init();
void Flush();

void SetFrameSize(float w, float h);

void SetAlbedo(std::shared_ptr<Texture2D> albedo);

int BatchCount();
int RenderTime();

void ResetStats();

void PushVertex(glm::vec2 pos, glm::vec3 color, glm::vec2 uv);
void PushVertex(Vertex2D v);
} // namespace gfx
} // namespace phnx
