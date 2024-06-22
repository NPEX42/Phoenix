#include <cstdint>
#include <cstdio>
#include <Phoenix/gfx/Texture.hpp>

#include <glad/glad.h>
#include <memory>
#include <stb/stb_image.h>

#include <Phoenix/Log.hpp>

#include <Phoenix/gfx/ogl/OGL.hpp>

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

    return std::make_shared<Texture2D>(w, h, pixels, GL_RGBA, filepath);
}

Texture2D::Texture2D(int width, int height, uint8_t *pixels, uint format, std::string filepath) {
    glCreateTextures(GL_TEXTURE_2D, 1, &mID);
    glBindTexture(GL_TEXTURE_2D, mID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_RGBA, (format == GL_RGBA ? GL_UNSIGNED_BYTE : GL_FLOAT), pixels);

    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    mWidth = width;
    mHeight = height;
    mFormat = format;
    mFilepath = filepath;
}

void Texture2D::SetUnit(int unit) {
    glActiveTexture(GL_TEXTURE0 + unit);
    Bind();
}

void Texture2D::Bind() { glBindTexture(GL_TEXTURE_2D, mID); }
void Texture2D::Unbind() { glBindTexture(GL_TEXTURE_2D, 0); }

void Texture2D::BindImage(int unit) { 
    glBindImageTexture(unit, mID, 0, GL_FALSE, 0, GL_READ_WRITE, mFormat);
}
void Texture2D::UnbindImage(int unit) { 
    glBindImageTexture(unit, 0, 0, GL_FALSE, 0, GL_READ_WRITE, mFormat); 
}

void Texture2D::Free() {
    glDeleteTextures(1, &mID);
    mID = 0;
}

void Texture2D::SetFilterModes(int min, int max) {
    Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, max);
    Unbind();
}


std::shared_ptr<Framebuffer> CreateFramebuffer(int width, int height, int colorBuffers) {
    auto fbo = std::make_shared<Framebuffer>();
    GL_CHECK(glGenFramebuffers(1, &fbo->ID));
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, fbo->ID));  
    GL_CHECK(glGenTextures(colorBuffers, fbo->ColorBuffer));
    uint32_t DRAW_BUFFERS[] = {
        GL_COLOR_ATTACHMENT0,
        GL_COLOR_ATTACHMENT1,
        GL_COLOR_ATTACHMENT2,
        GL_COLOR_ATTACHMENT3
    };
    for (int i = 0; i < colorBuffers; i++) {
        GL_CHECK(glBindTexture(GL_TEXTURE_2D, fbo->ColorBuffer[i]));

        GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_INT, NULL));

        GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
        GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST)); 
        GL_CHECK(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, fbo->ColorBuffer[i], 0)); 
        GL_CHECK(glDrawBuffers(colorBuffers, DRAW_BUFFERS));
        GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
    }

    fbo->Width = width;
    fbo->Height = height;
    fbo->ColorBufferCount = colorBuffers;
    
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {
        PHNX_INFO("Created FBO #%d", fbo->ID);
    } else {
        PHNX_ERR("Failed To Create FBO");
    }
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));


    return fbo;
}

void Framebuffer::Bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, ID);
}

void Framebuffer::Unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::Resize(int width, int height) {

    Width = width;
    Height = height;

    glDeleteTextures(ColorBufferCount, ColorBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, ID);  
    glGenTextures(ColorBufferCount, ColorBuffer);
    for (int i = 0; i < ColorBufferCount; i++) {
        glBindTexture(GL_TEXTURE_2D, ColorBuffer[i]);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, ColorBuffer[i], 0); 
        glDrawBuffer(GL_COLOR_ATTACHMENT0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    uint32_t DRAW_BUFFERS[] = {
        GL_COLOR_ATTACHMENT0,
        GL_COLOR_ATTACHMENT1,
        GL_COLOR_ATTACHMENT2,
        GL_COLOR_ATTACHMENT3
    };
    GL_CHECK(glDrawBuffers(ColorBufferCount, DRAW_BUFFERS));
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}


std::shared_ptr<Texture2D> CreateTexture2D(int width, int height, uint32_t *pixels, uint format) {
    return std::make_shared<Texture2D>(width, height, (uint8_t*) pixels, format);
}

uint32_t ImageFormatToGL(ImageFormat fmt) {
    switch (fmt) {
        case Grayscale8: return GL_R8;
        case Grayscale16: return GL_R16;
        case RGBA8: return GL_RGBA;
        case RGBA16: return GL_RGBA16;
        case RGBA16F: return GL_RGBA16F;
    }
}


std::shared_ptr<Framebuffer> CreateFramebuffer(int width, int height, const std::vector<ImageFormat>& formats) {
    auto fbo = std::make_shared<Framebuffer>();
    GL_CHECK(glGenFramebuffers(1, &fbo->ID));
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, fbo->ID));  
    GL_CHECK(glGenTextures(formats.size(), fbo->ColorBuffer));
    uint32_t DRAW_BUFFERS[] = {
        GL_COLOR_ATTACHMENT0,
        GL_COLOR_ATTACHMENT1,
        GL_COLOR_ATTACHMENT2,
        GL_COLOR_ATTACHMENT3
    };
    for (int i = 0; i < formats.size(); i++) {
        GL_CHECK(glBindTexture(GL_TEXTURE_2D, fbo->ColorBuffer[i]));

        GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, ImageFormatToGL(formats[i]), width, height, 0, formats[i], GL_UNSIGNED_INT, NULL));

        GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
        GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST)); 
        GL_CHECK(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, fbo->ColorBuffer[i], 0)); 
        GL_CHECK(glDrawBuffers(formats.size(), DRAW_BUFFERS));
        GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
    }

    fbo->Width = width;
    fbo->Height = height;
    fbo->ColorBufferCount = formats.size();
    
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {
        PHNX_INFO("Created FBO #%d", fbo->ID);
    } else {
        PHNX_ERR("Failed To Create FBO");
    }
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));


    return fbo;
}

} // namespace gfx
} // namespace phnx
