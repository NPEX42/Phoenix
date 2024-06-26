#include "Phoenix/Log.hpp"
#include "Phoenix/gfx/Api.hpp"
#include "glad/glad.h"
#include <Phoenix/gfx/ogl/Buffer.hpp>
#include <cstddef>
#include <cstdint>
#include <sys/types.h>

namespace GL {
    void Buffer::Bind() {
        GL_CHECK(glBindBuffer(mType, mID));
    }

    void Buffer::Unbind() {
        GL_CHECK(glBindBuffer(mType, 0));
    }

    uint32_t const Buffer::Size() {
        return mSize;
    }

    uint32_t const Buffer::Handle() {
        return mID;
    }

    Buffer::Buffer(phnx::gfx::BufferType type) : mID(0), mSize(0), mType(0) {
        mType = BufferTypeToGL(type);
        GL_CHECK(glGenBuffers(1, &mID));
        PHNX_INFO("Buffer ID: %d", mID);
    }

    void Buffer::SetLayout(int index, phnx::gfx::DataType type, int components, uint32_t stride, uint32_t offset) {
        GL_CHECK(glBindBuffer(mType, mID));
        uint32_t gl_type = DataTypeToGL(type);
        GL_CHECK(glVertexAttribPointer(index, components, gl_type, GL_FALSE, stride, (void*) (offset)));
        GL_CHECK(glEnableVertexAttribArray(index));
        GL_CHECK(glBindBuffer(mType, 0));
    }

    uint32_t BufferTypeToGL(phnx::gfx::BufferType type) {
        switch (type) {
            case phnx::gfx::VERTEX: return GL_ARRAY_BUFFER;
            case phnx::gfx::INDEX: return GL_ELEMENT_ARRAY_BUFFER;
            case phnx::gfx::DRAW_ARGS: return GL_DRAW_INDIRECT_BUFFER;
            case phnx::gfx::UNIFORM: return GL_UNIFORM_BUFFER;
        }
        return GL_ARRAY_BUFFER;
    }

    template<>
    void Buffer::SetData(const uint16_t* data, uint32_t size) {
                if (mHasAllocated) {
                    GL_CHECK(glBufferSubData(mType, 0, size * sizeof(uint16_t), data));
                } else {
                    PHNX_DEBUG("Allocated %d Bytes In VBO %d", size * sizeof(uint16_t), mID);
                    GL_CHECK(glBufferData(mType, size * sizeof(uint16_t), data, GL_STREAM_DRAW));
                    mHasAllocated = true;
                }
            }

            template<>
    void Buffer::SetData(const phnx::Vertex* data, uint32_t size) {
                if (mHasAllocated) {
                    GL_CHECK(glBufferSubData(mType, 0, size * sizeof(phnx::Vertex), data));
                } else {
                    PHNX_DEBUG("Allocated %d Bytes In VBO %d", size * sizeof(phnx::Vertex), mID);
                    GL_CHECK(glBufferData(mType, size * sizeof(phnx::Vertex), data, GL_STREAM_DRAW));
                    mHasAllocated = true;
                }
            }


    void Buffer::Destroy() {
        glDeleteBuffers(1, &mID);
    }

    void* Buffer::Map() {
        Bind();
        void* ptr = glMapBuffer(mType, GL_READ_WRITE);
        Unbind();
        return ptr;
    }

    void Buffer::Unmap() {
        Bind();
        glUnmapBuffer(mType);
        Unbind();
    }

    void Buffer::Reserve(uint32_t size) {
        GL_CHECK(glBufferData(mType, size, nullptr, GL_STREAM_DRAW));
    }
}