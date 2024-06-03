#pragma once

#include "glm/ext/vector_float2.hpp"
#include <cstdint>
#include <memory>
#include <string>
namespace phnx {
namespace gfx {
class Texture2D {
public:
    Texture2D(int width, int height, uint8_t *pixels);
    void Bind();
    void Unbind();
    uint32_t ID() { return mID; }
    float Width() { return mWidth; }
    float Height() { return mHeight; }

    glm::vec2 Size() { return {mWidth, mHeight}; }

    void SetUnit(int unit);

private:
    uint32_t mID;
    float mWidth, mHeight;
};

std::shared_ptr<Texture2D> LoadTexture2D(std::string filepath, bool flip = false);

} // namespace gfx
} // namespace phnx
