#include "Phoenix/Common.hpp"
#include "glad/glad.h"
#include "glm/ext/vector_float3.hpp"
#include "glm/ext/vector_float4.hpp"
#include "glm/gtx/transform.hpp"

#include <Phoenix/gfx/ogl/GLRenderPipeline.hpp>
#include <cstddef>

namespace phnx
{
void GLRenderPipeline::ClearColor(const glm::vec4& color)
{
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void GLRenderPipeline::SetPosition(const glm::vec3& pos) { mPosition = pos; }

void GLRenderPipeline::SetRotation(const glm::vec3& rot) { mRotation = rot; }

void GLRenderPipeline::SetScale(const glm::vec3& scale) { mScale = scale; }

void GLRenderPipeline::DrawMesh(const Ref<Mesh> mesh)
{
    if (mShader) {
        mShader->Bind();
    }

    glm::mat4 translation = glm::translate(mPosition);
    glm::mat4 rotation = glm::mat4(1);

    rotation = glm::rotate(rotation, mRotation.x, {1, 0, 0});
    rotation = glm::rotate(rotation, mRotation.y, {0, 1, 0});
    rotation = glm::rotate(rotation, mRotation.z, {0, 0, 1});

    glm::mat4 scale = glm::scale(mScale);

    glm::mat4 transform = translation * rotation * scale;

    if (mShader) {
        mShader->SetMatrix4("uModelMat", transform);
    }

    mesh->Bind();
    glDrawElements(GL_TRIANGLES, mesh->IndexCount(), GL_UNSIGNED_SHORT, nullptr);
    mesh->Unbind();
}

void GLRenderPipeline::SetShader(const Ref<gfx::Shader>& shader) {
    mShader = shader;
}

Ref<RenderPipeline> CreateGLPipeline() { return MakeRef<GLRenderPipeline>(); }

} // namespace phnx