#include "Phoenix/Application2D.hpp"
#include "Phoenix/AssetManager.hpp"
#include "Phoenix/gfx/Renderer2D.hpp"
#include "Phoenix/gfx/Shader.hpp"
#include "Phoenix/gfx/Texture.hpp"
#include "Phoenix/project/ECS.hpp"
#include "Phoenix/project/Entity.hpp"
#include "Phoenix/project/Project.hpp"
#include "Phoenix/project/Scene.hpp"
#include "fmt/core.h"
#include "glad/glad.h"
#include "glm/ext/vector_float2.hpp"
#include "imgui.h"
#include "toml/value.hpp"
#include <Phoenix.hpp>
#include <Phoenix/gfx/ui.hpp>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include <sys/types.h>

#include <Phoenix/project/Component.hpp>
#include <vector>

#include <Phoenix/RenderPipeline.hpp>

using namespace phnx::ecs;
using namespace phnx;

class Editor : public phnx::Application2D {

    bool mRunning = true, mProjectInfo = false;
    std::shared_ptr<phnx::Project> mProject;

    std::shared_ptr<phnx::ecs::Entity> mCurrentEntity;


    std::shared_ptr<phnx::gfx::Framebuffer> mViewport;

    phnx::gfx::Shader* mShader;

    float mViewportScale = 1.0f;

    char mTagBuffer[128]; 

    std::shared_ptr<phnx::Scene> mScene;

    void SerializeEntity(toml::value& table, std::shared_ptr<Entity> ent) {

        if (ent->HasComponent<Tag>()) {
            SerializeComponent(table, ent->GetComponent<Tag>());
        }

        if (ent->HasComponent<Transform>()) {
            SerializeComponent(table, ent->GetComponent<Transform>());
        }

        if (ent->HasComponent<SpriteRenderer>()) {
            SerializeComponent(table, ent->GetComponent<SpriteRenderer>());
        }
    }


    bool OnCreate() override {
        mProject = phnx::LoadProject("TestProject");
        phnx::AssetManager::LoadTexturesFromTOML(mProject->AssetDir() + "/textures.toml");
        mViewport = phnx::gfx::CreateFramebuffer(720, 480, 4);
        mShader = phnx::gfx::Shader::Load("res/shaders/simple.vs", "res/shaders/simple.frag");

        mScene = std::make_shared<phnx::Scene>();

        return true;
    }

    bool OnUpdate() override {
        return mRunning;
    }

    void OnRender() override {
        mViewport->Bind();
        phnx::gfx::SetFrameSize(mViewport->Width, mViewport->Height);
        mShader->Bind();
        phnx::gfx::Clear(0.1, 0.2, 0.3, 1.0f);

        mScene->Render();

        if (mCurrentEntity) {
            if(mCurrentEntity->HasComponent<Transform>()) {
                auto& t = mCurrentEntity->GetComponent<Transform>();
                if (mCurrentEntity->HasComponent<SpriteRenderer>()) {
                    auto& sr = mCurrentEntity->GetComponent<SpriteRenderer>();
                    phnx::gfx::SetAlbedo(phnx::AssetManager::GetTextureByName(sr.TextureID));
                }
                phnx::gfx::RotatedQuad(t.Position, t.Rotation, t.Scale);
            }
        }
        phnx::gfx::Flush();
        mShader->Unbind();
        mViewport->Unbind();
    }

    void OnDestroy() override {

    }

    void OnImGui() override {
        phnx::ui::Dockspace();

        ImGui::ShowDemoWindow();
        bool deleteEntity = false;

            if (ImGui::Begin("Entities")) {
                for (auto entity : phnx::ecs::GetAllEntitiesWith<Tag>()) {
                    auto& tag = phnx::ecs::GetComponent<Tag>(entity);
                    if (ImGui::Selectable((fmt::format("{} - {}", tag.Tag, tag.UUID)).c_str())) {
                        mCurrentEntity = std::make_shared<phnx::ecs::Entity>(entity);
                        
                        strcpy(mTagBuffer, tag.Tag.c_str());
                    }
                }
            ImGui::End();
            }
        if (ImGui::Begin("Inspector", NULL, ImGuiWindowFlags_MenuBar)) {
            if (mCurrentEntity) {

                if (mCurrentEntity->HasComponent<Tag>()) {
                    auto& tag = mCurrentEntity->GetComponent<Tag>();
                    
                    if (ImGui::InputText("##TagInput", mTagBuffer, 128) && strlen(mTagBuffer)) {
                        tag.Tag = mTagBuffer;
                    }
                }

                ImGui::SameLine();
                if (ImGui::Button("Delete")) {
                    deleteEntity = true;
                }

                if (mCurrentEntity->HasComponent<Transform>()) {
                    auto& transform = mCurrentEntity->GetComponent<Transform>();
                    ImGui::SeparatorText("Transform");
                    ImGui::DragFloat2("Position", &transform.Position.x);
                    ImGui::DragFloat2("Scale", &transform.Scale.x);
                    ImGui::SliderAngle("Rotation", &transform.Rotation);
                }

                if (mCurrentEntity->HasComponent<SpriteRenderer>()) {
                    auto& sprite = mCurrentEntity->GetComponent<SpriteRenderer>();
                    ImGui::SeparatorText("Sprite");
                    if (ImGui::BeginCombo("ID", sprite.TextureID.c_str())) {
                        for (auto& entry : phnx::AssetManager::Textures()) {
                            if (ImGui::Selectable(entry.first.c_str())) {
                                sprite.TextureID = entry.first;
                            }
                        }
                        ImGui::EndCombo();
                    }
                }

                if (ImGui::BeginPopupContextItem("ComponentList")) {
                    if (!mCurrentEntity->HasComponent<Transform>() && ImGui::Selectable("Transform")) {
                        mCurrentEntity->AddComponent<Transform>(glm::vec2 {0, 0}, glm::vec2 {100, 100}, 0);
                    }

                    if (!mCurrentEntity->HasComponent<SpriteRenderer>() && ImGui::Selectable("Sprite")) {
                        mCurrentEntity->AddComponent<SpriteRenderer>("White");
                    }
                    ImGui::EndPopup();
                }

                if (ImGui::Button("+")) {

                    ImGui::OpenPopup("ComponentList");
                }

                if (deleteEntity) {
                    mCurrentEntity->Delete();
                    mCurrentEntity = nullptr;
                }
            }
            
        }
        ImGui::End();

        if (ImGui::Begin("Renderer Info")) {
            ImGui::Text("OpenGL Version: %s", glGetString(GL_VERSION));
            ImGui::Text("Framerate: %d", FrameRate());
        }
        ImGui::End();
            if (mProjectInfo) {
            if (ImGui::Begin("Project Info", &mProjectInfo) && mProject) {
                ImGui::Text("Base Directory: %s", mProject->BaseDir().c_str());
                ImGui::Text("Assets Directory: %s", mProject->AssetDir().c_str());
                ImGui::Text("Script Directory: %s", mProject->ScriptDir().c_str());
            }

            ImGui::End();
        }

        if (ImGui::Begin("Viewport")) {
            ImVec2 size =  ImGui::GetContentRegionAvail();
            ImGui::Image((ImTextureID)((uint64_t) mViewport->ColorBuffer[0]), {mViewport->Width * mViewportScale, mViewport->Height * mViewportScale}, {0, 1}, {1, 0});
        }
        ImGui::End();


        if (ImGui::Begin("ID View")) {
            ImVec2 size =  ImGui::GetContentRegionAvail();
            ImGui::Image((ImTextureID)((uint64_t) mViewport->ColorBuffer[1]), {mViewport->Width * mViewportScale, mViewport->Height * mViewportScale}, {0, 1}, {1, 0});
        }
        ImGui::End();
    }

    void OnImGuiMainMenu() override {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Quit")) {
                mRunning = false;
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("View")) {
            if (ImGui::MenuItem("Project Info")) { mProjectInfo = true; }
            ImGui::EndMenu();
        }

        if (ImGui::MenuItem("Create Entity")) {
                mCurrentEntity = mScene->CreateEntity();
                mCurrentEntity->AddComponent<Transform>(glm::vec2 {0, 0}, glm::vec2 {100, 100}, 0);
                strcpy(mTagBuffer, mCurrentEntity->GetComponent<Tag>().Tag.c_str());
        }

        if (ImGui::MenuItem("Save Entity") && mCurrentEntity) {
            toml::value table = toml::value();

            SerializeEntity(table, mCurrentEntity);

            std::cout << table << std::endl;
        }
    }

    phnx::WindowSpec WindowSpecs() override {
        return phnx::WindowSpec {
            .Width = 1080,
            .Height = 720,
            .Title = "Editor",
            .Vsync = true,
        };
    }


};

phnx::Application2D* CreateApp() {
    return new Editor();
}