#pragma once
#include <Phoenix/gfx/ogl/OGL.hpp>
#include <cstdint>
#include "../Api.hpp"
#include "Phoenix/Log.hpp"
#include "glad/glad.h"

namespace GL {


    class Buffer : public phnx::gfx::IBuffer {
        public:

            virtual void Bind();
            virtual void Unbind();
            virtual uint32_t const Size();
            virtual uint32_t const Handle();
            template<typename T>
            void SetData(T* data, uint32_t size) {
                if (mHasAllocated) {
                    GL_CHECK(glBufferSubData(mType, 0, size * sizeof(T), data));
                } else {
                    PHNX_DEBUG("Allocated %d Bytes In VBO %d", size * sizeof(T), mID);
                    GL_CHECK(glBufferData(mType, size * sizeof(T), data, GL_STREAM_DRAW));
                    mHasAllocated = true;
                }
            }

            virtual void SetLayout(int index, phnx::gfx::DataType type, int components, uint32_t stride, uint32_t offset);

            Buffer(phnx::gfx::BufferType type);       
    private:
        uint32_t mID = 0, mSize = 0, mType = GL_ARRAY_BUFFER;
        bool mHasAllocated = false;
    };


    uint32_t BufferTypeToGL(phnx::gfx::BufferType type);
}