#pragma once
#include <cstdint>
#include <vector>
#include "Phoenix/Common.hpp"
#include "gfx/Api.hpp"
namespace phnx {
    class Mesh {
        public:
            Mesh();

            void Bind();
            void Unbind();

            uint16_t TriangleCount() const {return mIndexCount / 3;}
            uint16_t VertexCount() const {return mVertexCount;}
            uint16_t IndexCount() const {return mIndexCount;}

            uint32_t Size() const {return (mIndexCount * sizeof(uint16_t)) + (mVertexCount * sizeof(Vertex));}

            void SetVertices(const std::vector<Vertex>& vertices);
            void SetTriangles(const std::vector<uint16_t>& indices);
        private:
            uint32_t mID = 0;
            uint16_t mIndexCount = 0, mVertexCount = 0;
            Ref<gfx::IBuffer> mVBO, mIBO;
    };
}