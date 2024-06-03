#include <cstdint>
#include <cstdio>
#include <gfx/Texture.hpp>

#include <glad/glad.h>
#include <memory>
#include <stb/stb_image.h>

namespace phnx {
namespace gfx {

std::shared_ptr<Texture2D> LoadTexture2D(std::string filepath, bool flip) {
    int w, h, channels;
    stbi_set_flip_vertically_on_load(flip ? 0 : 1);
    stbi_uc *pixels = stbi_load(filepath.c_str(), &w, &h, &channels, 4);
    if (pixels == nullptr) {
        printf("Failed To Load Texture '%s'\n", filepath.c_str());
        return nullptr;
    }

    return std::make_shared<Texture2D>(w, h, pixels);
}

Texture2D::Texture2D(int width, int height, uint8_t *pixels) {
    glCreateTextures(GL_TEXTURE_2D, 1, &mID);
    glBindTexture(GL_TEXTURE_2D, mID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    mWidth = width;
    mHeight = height;
}

void Texture2D::SetUnit(int unit) {
    glActiveTexture(GL_TEXTURE0 + unit);
    Bind();
}

void Texture2D::Bind() { glBindTexture(GL_TEXTURE_2D, mID); }
void Texture2D::Unbind() { glBindTexture(GL_TEXTURE_2D, 0); }

} // namespace gfx
} // namespace phnx
