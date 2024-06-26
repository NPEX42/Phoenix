#pragma once
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <glad/glad.h>
#include "Phoenix/Mesh.hpp"
#include "Phoenix/Common.hpp"
#include "Phoenix/gfx/Api.hpp"
#include <Phoenix/gfx/ogl/Buffer.hpp>
#include <vector>
namespace phnx {
    Mesh::Mesh() {
        glGenVertexArrays(1, &mID);
        mVBO = MakeRef<GL::Buffer>(gfx::VERTEX);
        mIBO = MakeRef<GL::Buffer>(gfx::INDEX);

        glBindVertexArray(mID);
        mVBO->Bind();
        uint32_t stride = sizeof(Vertex);
        mVBO->SetLayout(0, gfx::F32, 3, stride, offsetof(Vertex, Position));
        mVBO->SetLayout(1, gfx::F32, 2, stride, offsetof(Vertex, TexCoord));
        mVBO->SetLayout(2, gfx::F32, 3, stride, offsetof(Vertex, Normal));
        mVBO->Unbind();

        mIBO->Bind();

        glBindVertexArray(0);
    }

    void Mesh::Bind() {
        glBindVertexArray(mID);
        mIBO->Bind();
    }

    void Mesh::Unbind() {
        glBindVertexArray(0);
        mIBO->Unbind();
    }

    void Mesh::SetVertices(const std::vector<Vertex>& vertices) {
        mVBO->Bind();
        mVBO->Reserve(sizeof(Vertex) * vertices.size());
        void* dest = mVBO->Map();
        std::memcpy(dest, vertices.data(), sizeof(Vertex) * vertices.size()); 
        mVBO->Unmap();
        mVBO->Unbind();

        mVertexCount = vertices.size();
    }   

    void Mesh::SetTriangles(const std::vector<uint16_t>& indices) {
        mIBO->Bind();
        mIBO->Reserve(sizeof(uint16_t) * indices.size());
        void* dest = mIBO->Map();
        std::memcpy(dest, indices.data(), sizeof(uint16_t) * indices.size()); 
        mIBO->Unmap();
        mIBO->Unbind();

        mIndexCount = indices.size();
    }


}