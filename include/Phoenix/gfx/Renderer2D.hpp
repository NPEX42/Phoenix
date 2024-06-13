#pragma once

#include "Phoenix/gfx/Texture.hpp"
#include "Phoenix/gfx/TextureAtlas.hpp"
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
void Quad(const glm::vec2 &ctr,const glm::vec2 &size = {1, 1},const glm::vec3 &color = {1, 1, 1}, const glm::vec2& uv0 = {0, 0}, const glm::vec2& uv1 = {1, 1});

void TextureRect(std::shared_ptr<Texture2D> texture, const glm::vec2 &ctr, const Rect& rect, const glm::vec2 &size = {1, 1},const glm::vec3 &color = {1, 1, 1});

void RotatedQuad(const glm::vec2 &ctr, float angle,const glm::vec2 &size = {1, 1},const glm::vec3 &color = {1, 1, 1}, const glm::vec2& uv0 = {0, 0}, const glm::vec2& uv1 = {1, 1});

void Init();
void Flush();

void SetFrameSize(float w, float h);

float FrameWidthF();
float FrameHeightF();

int FrameWidth();
int FrameHeight();

void SetAlbedo(std::shared_ptr<Texture2D> albedo);

int BatchCount();
int RenderTime();

void ResetStats();

void PushVertex(glm::vec2 pos, glm::vec3 color, glm::vec2 uv);
void PushVertex(Vertex2D v);
} // namespace gfx
} // namespace phnx
