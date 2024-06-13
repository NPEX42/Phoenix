#pragma once
#include <cstdint>
namespace phnx {
    namespace gfx {
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
            void SetData(T* data, uint32_t size);

            virtual void SetLayout(int index, DataType type, int components, uint32_t stride, uint32_t offset) = 0;
        };
    }
}