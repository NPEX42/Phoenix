#pragma once

#include "glm/ext/vector_float2.hpp"
#include <cstdint>
#include <memory>
#include <string>
#include <sys/types.h>
#include <glad/glad.h>
namespace phnx {
namespace gfx {
class Texture2D {
public:
    Texture2D(int width, int height, uint8_t *pixels, uint format = GL_RGBA);
    void Bind();
    void Unbind();

    void BindImage(int unit);
    void UnbindImage(int unit);

    uint32_t ID() { return mID; }
    float Width() { return mWidth; }
    float Height() { return mHeight; }

    glm::vec2 Size() { return {mWidth, mHeight}; }

    void SetUnit(int unit);

    const float  Aspect() {return ((float) mHeight / (float) mWidth); }

    void Free();

    void SetFilterModes(int min, int max);

private:
    uint32_t mID, mFormat;
    float mWidth, mHeight;
};

std::shared_ptr<Texture2D> LoadTexture2D(std::string filepath, bool flip = false);
std::shared_ptr<Texture2D> CreateTexture2D(int width, int height, uint32_t *pixels, uint format = GL_RGBA);

struct Framebuffer {
    int Width, Height, ColorBufferCount;
    uint32_t ID;
    uint32_t ColorBuffer[4];
    uint32_t DepthStencilBuffer;

    void Bind();
    void Unbind();

    void Resize(int width, int height);

    const float  Aspect() {return ((float) Height / (float) Width); }
};

std::shared_ptr<Framebuffer> CreateFramebuffer(int width, int height, int colorBuffers);

} // namespace gfx
} // namespace phnx
