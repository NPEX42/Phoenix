#pragma once
#include "glm/glm.hpp"
#include <cstdint>
namespace phnx {

    struct Vertex {
        glm::vec3 Position;
        glm::vec2 TexCoord;
        glm::vec3 Normal;
    };

namespace gfx {
    enum BufferType {
        VERTEX, INDEX, DRAW_ARGS, UNIFORM
    };

    enum DataType {
            F32, F64, U8, U16, U32, U64, S8, S16, S32, S64
    };

    class IBuffer {
        public:

            virtual void Bind() = 0;
            virtual void Unbind() = 0;
            virtual uint32_t const Size() = 0;
            virtual uint32_t const Handle() = 0;
            template<typename T>
            void SetData(const T* data, uint32_t size);

            virtual void SetLayout(int index, DataType type, int components, uint32_t stride, uint32_t offset) = 0;

            virtual void Destroy() = 0;

            virtual void* Map() = 0;
            virtual void  Unmap() = 0;

            virtual void Reserve(uint32_t size) = 0;
        };
    }


}