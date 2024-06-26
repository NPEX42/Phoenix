#pragma once

#include "../../RenderPipeline.hpp"
#include "Phoenix/Common.hpp"
#include "Phoenix/gfx/Shader.hpp"
#include "glm/ext/vector_float3.hpp"

namespace phnx {
    class GLRenderPipeline : public RenderPipeline {
    public:
        virtual void SetPosition(const glm::vec3& position) override;
        virtual void SetRotation(const glm::vec3& rotation) override;
        virtual void SetScale(const glm::vec3& scale) override;
        virtual void ClearColor(const glm::vec4& color) override;
        virtual void DrawMesh(const Ref<Mesh> mesh) override;

        virtual void SetShader(const Ref<gfx::Shader>& shader) override;

    private:
        glm::vec3 
            mPosition = {0, 0, 0}, 
            mScale = {1, 1, 1}, 
            mRotation = {0, 0, 0}
        ;

        Ref<gfx::Shader> mShader;


    };


    Ref<RenderPipeline> CreateGLPipeline();
    

}