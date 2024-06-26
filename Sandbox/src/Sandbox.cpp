#include "Phoenix/Application2D.hpp"
#include "Phoenix/AssetManager.hpp"
#include <Phoenix/Graphics.hpp>
#include "Phoenix/Camera.hpp"
#include "Phoenix/Common.hpp"
#include "Phoenix/Log.hpp"
#include "Phoenix/Mesh.hpp"
#include "Phoenix/MeshImporter.hpp"
#include "Phoenix/RenderPipeline.hpp"
#include "Phoenix/Util.hpp"
#include <Phoenix/gfx/ui.hpp>
#include "Phoenix/gfx/ogl/GLRenderPipeline.hpp"
#include "Phoenix/scripting/Script.hpp"
#include "fmt/core.h"
#include "glad/glad.h"
#include "glm/ext/vector_float2.hpp"
#include "glm/trigonometric.hpp"
#include "imgui.h"
#include "nfd.h"
#include "yaml-cpp/node/node.h"
#include <Phoenix.hpp>
#include <cmath>
#include <cstddef>
#include <cstring>
#include <memory>
#include <string>

#include <nfd.hpp>
#include <vector>

using namespace phnx;

class Sandbox : public phnx::Application2D {

    std::shared_ptr<RenderPipeline> mPipeline;
    Ref<Mesh> mMesh;
    Ref<ICamera> mCamera;
    Ref<gfx::Shader> mShader;

    glm::vec3 mCamPos = {00, 0, 10}, mCamRot = {0, 0, 0}, mMeshPos = {0, 0, 0}, mMeshRot = {0, 0, 0};

    bool OnCreate() override {
        mPipeline = CreateGLPipeline();
        mShader = phnx::gfx::LoadShader("res/shaders/unlit/Simple.vs.glsl", "res/shaders/unlit/Simple.fs.glsl");
        
        mShader->Validate();
        
        mMesh = ImportFBX("res/meshes/Quad.obj");
        mCamera = MakeRef<PerspectiveCamera>();
        mCamera->RecalculateProjection();

        mCamera->SetPosition(mCamPos);
        mCamera->SetRotation(mCamRot);

        mShader->Bind();
        mShader->SetFloat4("uTint", 1, 1, 1, 1);
        mShader->SetMatrix4("uVP", mCamera->ProjectionMatrix() * mCamera->ViewMatrix());
        mPipeline->SetShader(mShader);

        mCamera->SetFarPlane(10000);
        return true;
    }

    bool OnUpdate() override {

        mMeshRot.y += DeltaTime() * glm::radians<float>(10);

        return true;
    }

    void OnRender() override {
        
        mPipeline->ClearColor({0.1, 0.2, 0.3, 1.0});
        mPipeline->SetScale({100, 100, 100});
        mPipeline->SetRotation(mMeshRot);
        mPipeline->SetPosition(mMeshPos);
        mPipeline->DrawMesh(mMesh);
    }

    void OnDestroy() override {
    }

    void OnImGui() override {
        ImGui::Text("Triangles: %d", mMesh->TriangleCount());
        ImGui::Text("Vertices: %d", mMesh->VertexCount());
        ImGui::Text("Mesh Size: %d Bytes", mMesh->Size());

        ImGui::SeparatorText("Camera Controls");
        if (ImGui::DragFloat3("Position##Cam", &mCamPos.x, 0.1f)) {
            mCamera->SetPosition(mCamPos);
            mShader->SetMatrix4("uVP", mCamera->ProjectionMatrix() * mCamera->ViewMatrix());
        }

        if (ImGui::DragFloat3("Rotation##Cam", &mCamRot.x, 0.01, -2*M_PI, 2 * M_PI)) {
            mCamera->SetRotation(mCamRot);
            mShader->SetMatrix4("uVP", mCamera->ViewProjection());
        }

        if (ImGui::Button("Reset")) {
            mCamera->SetPosition({0, 0, 10});
            mCamera->SetRotation({0, 0, 0});
            mShader->SetMatrix4("uVP", mCamera->ViewProjection());

            mCamPos = mCamera->Position();
            mCamRot = mCamera->Rotation();
        }

        ImGui::SeparatorText("Mesh Controls");

        ImGui::DragFloat3("Position##Mesh", &mMeshPos.x);
    }

    phnx::WindowSpec WindowSpecs() override {
        return phnx::WindowSpec {
            .Width = 1080,
            .Height = 720,
            .Title = "Sandbox",
            .Vsync = true,
        };
    }


};



phnx::Application2D* CreateApp() {
    return new Sandbox();
    
}