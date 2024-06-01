#pragma once

#include "glm/detail/qualifier.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float3.hpp"
#include <glm/vec3.hpp>

#include <cstdint>
namespace phnx {
namespace gfx {
void Clear(float r, float g, float b, float a);
void Quad(float cx, float cy, float w, float y, glm::vec3 &color);

void Init();
void Flush();

void PushVertex(glm::vec3 pos, glm::vec3 color, glm::vec2 uv);
} // namespace gfx
} // namespace phnx
