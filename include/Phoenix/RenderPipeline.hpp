#pragma once

#include "Phoenix/Mesh.hpp"
#include "Phoenix/gfx/Shader.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/ext/vector_float4.hpp"

namespace phnx {
    class RenderPipeline {
        public:
            virtual void SetPosition(const glm::vec3& position) = 0;
            virtual void SetRotation(const glm::vec3& rotation) = 0;
            virtual void SetScale(const glm::vec3& scale) = 0;
            virtual void ClearColor(const glm::vec4& color) = 0;
            virtual void DrawMesh(const Ref<Mesh> mesh) = 0;
            virtual void SetShader(const Ref<gfx::Shader>& shader) = 0;
    };

}