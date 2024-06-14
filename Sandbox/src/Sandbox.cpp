#include "Phoenix/Application2D.hpp"
#include "Phoenix/AssetManager.hpp"
#include <Phoenix/Graphics.hpp>
#include "Phoenix/Log.hpp"
#include "Phoenix/Util.hpp"
#include <Phoenix/gfx/ui.hpp>
#include "Phoenix/scripting/Script.hpp"
#include "fmt/core.h"
#include "glad/glad.h"
#include "glm/ext/vector_float2.hpp"
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

class Sandbox : public phnx::Application2D {

    bool mShowDemoWindow = false;
    std::shared_ptr<phnx::gfx::Framebuffer> mFB;

    std::shared_ptr<phnx::gfx::Texture2D> mSnom, mComputeOutput;

    float mScale = 0, mViewportScale = 1.0f;
    glm::vec2 pos;

    phnx::gfx::Shader* mShader = nullptr;

    YAML::Node mConfig;

    std::string mActiveTextureName;
    char nameBuffer[128];

    std::shared_ptr<phnx::gfx::ComputeShader> mCompute;

    std::shared_ptr<phnx::gfx::TextureAtlas> mAtlas;
    std::string mTileID;

    std::vector<std::shared_ptr<phnx::SpriteScript>> mScripts;


    #define MAX_SPRITES (1024)

    bool OnCreate() override {

        NFD::Init();

        mConfig = phnx::LoadYAML("res/config.yaml");
        mFB = phnx::gfx::CreateFramebuffer(mConfig["Viewport"]["Width"].as<int>(), mConfig["Viewport"]["Height"].as<int>(), 2);
        
        mShader = phnx::gfx::Shader::Load("res/shaders/simple.vs", "res/shaders/simple.frag");
        phnx::gfx::SetFrameSize(mFB->Width, mFB->Height);
        mShader->SetInt("uAlbedo", 0);

        phnx::AssetManager::LoadTexturesFromTOML("res/textures.toml");
        mSnom = phnx::AssetManager::GetTextureByName("Snom");

        phnx::gfx::SetAlbedo(mSnom);

        mActiveTextureName = "Snom";

        mCompute = phnx::gfx::ComputeShader::Load("res/shaders/uv.compute");

        mComputeOutput = phnx::gfx::CreateTexture2D(mFB->Width, mFB->Height, nullptr, GL_RGBA32F);

        mComputeOutput->BindImage(0);
        mCompute->SetInt("imgOutput", 0);
        mCompute->SetInt("imageInput", 1);
        mCompute->SetFloat("uRadius", mScale);


        glBindImageTexture(1, mFB->ColorBuffer[0], 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA8);

        mCompute->DispatchSync(mFB->Width,mFB->Height);

        mAtlas = std::make_shared<phnx::gfx::TextureAtlas>(phnx::AssetManager::GetTextureByName("Tiles"));
        mAtlas->GenerateTiles(16, 16);

        mAtlas->Texture()->SetFilterModes(GL_NEAREST, GL_NEAREST);
        
        for (int i = 0; i < MAX_SPRITES; i++) {
            mScripts.push_back(std::make_shared<phnx::SpriteScript>("res/scripts/test.lua"));
            mScripts[i]->Init();
        }

        return true;
    }

    bool OnUpdate() override {
        for (int i = 0; i < MAX_SPRITES; i++) {
            mScripts[i]->Update();
        }
        return true;
    }

    void OnRender() override {
        mFB->Bind();
        mShader->Bind();
        phnx::gfx::SetAlbedo(mSnom);
        phnx::gfx::Clear(0.0f, 0.2f, 0.3f, 1.0f);
        //phnx::gfx::Quad(pos, {50, 50 * mSnom->Aspect()}, {1, 1, 1});
        //phnx::gfx::TextureRect(mAtlas->Texture(), {128, 128}, mAtlas->GetTileRect(mTileID), {256, 256});
        for (int i = 0; i < MAX_SPRITES; i++) {
            mScripts[i]->Render();
        }

        phnx::gfx::Flush();
        mFB->Unbind();

        mCompute->DispatchSync(mFB->Width, mFB->Height);
    }

    void OnDestroy() override {
        ImGui::SaveIniSettingsToDisk("imgui.ini");
        phnx::SaveYAML("res/config.yaml", mConfig);

        mAtlas->ExportTOML("res/tiles.toml");
    }

    void OnImGui() override {
        phnx::ui::Dockspace();
        ImGui::Begin("Properties", NULL, ImGuiWindowFlags_MenuBar);
        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("Debug")) {
                if (ImGui::MenuItem("Demo Window")) {
                    mShowDemoWindow = true;
                }

                if (ImGui::MenuItem("Reload Config")) {
                    mConfig = phnx::LoadYAML("res/config.yaml");
                    mFB->Resize(mConfig["Viewport"]["Width"].as<int>(), mConfig["Viewport"]["Height"].as<int>());
                    phnx::gfx::SetFrameSize(mFB->Width, mFB->Height);
                    phnx::AssetManager::ReloadTexturesFromTOML("res/textures.toml");
                    mSnom = phnx::AssetManager::GetTextureByName(mActiveTextureName);
                }

                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        if (ImGui::SliderFloat("Scale", &mScale, 0, 2 * M_PI)) {
            mCompute->SetFloat("uRadius", mScale);
        }
        ImGui::SliderFloat("Viewport Scale", &mViewportScale, 0.01f, 10.0f);
        if (ImGui::SliderFloat2("Snom Position", &pos.x, 0, mFB->Width)) {
            mCompute->SetFloat2("uPosition", pos.x, pos.y);
        }
        ImGui::Text("Viewport Size: %dx%d", phnx::gfx::FrameWidth(), phnx::gfx::FrameHeight());
        ImGui::Text("FPS: %d", FrameRate());
        ImGui::End();

        ImGui::Begin("Viewport");
        ImGui::Image(
            (ImTextureID) (uint64_t)mFB->ColorBuffer[0], 
            {mFB->Width * mViewportScale, mFB->Height * mViewportScale},
            {0, 1}, {1, 0}
            );
        ImGui::End();


        ImGui::Begin("Texture Manager");
        if (ImGui::BeginCombo("Current Texture", mActiveTextureName.c_str())) {
            for (const auto& texture : phnx::AssetManager::Textures()) {
                if (ImGui::Selectable(texture.first.c_str(), mActiveTextureName == texture.first)) {
                    mActiveTextureName = texture.first;
                    phnx::gfx::SetAlbedo(phnx::AssetManager::GetTextureByName(mActiveTextureName));

                    strcpy(nameBuffer, mActiveTextureName.c_str());
                }
            }
            ImGui::EndCombo();
        }
        
        (ImGui::InputText("Name", nameBuffer, 128));

        if (ImGui::ImageButton("##TextureSelection", (ImTextureID)(uint64_t) mSnom->ID(), {128, 128 * mSnom->Aspect()})) {
            nfdchar_t* path;
            nfdresult_t result = NFD_OpenDialog(&path, nullptr, 0, nullptr);
            if (result == NFD_OKAY) {
                PHNX_INFO("Path: %s", path);
                phnx::AssetManager::LoadTexture2D(mActiveTextureName, path);
            }
        }

    

        if (ImGui::Button("Update") && strlen(nameBuffer) > 0) {
            mActiveTextureName = nameBuffer;
            phnx::AssetManager::SetTextureByName(nameBuffer, mSnom);
        }
        
        if (ImGui::BeginChild("Tilemap", {20 * 16 + 24, 8 * 16 + 24}, ImGuiChildFlags_Border | ImGuiChildFlags_ResizeX | ImGuiChildFlags_ResizeY)) {

        for (int y = 0; y < mAtlas->Rows(); y++) {
            for (int x = 0; x < mAtlas->Columns(); x++) {
                phnx::gfx::RectUVs uvs = mAtlas->GetTileRectUV(fmt::format("tile_{}_{}", x, y));

                ImGui::Image((ImTextureID)(uint64_t) mAtlas->Texture()->ID(), {32, 32},
                    {uvs.UV0.x, uvs.UV0.y}, {uvs.UV1.x, uvs.UV1.y}
                );

                if (ImGui::IsItemClicked(ImGuiMouseButton_Left)) {
                    mTileID = fmt::format("tile_{}_{}", x, y);
                }

                ImGui::SameLine(0, 3);
            }
             ImGui::NewLine();
        }
        ImGui::EndChildFrame();
        }
        ImGui::End();

        if (mShowDemoWindow) {
            ImGui::ShowDemoWindow(&mShowDemoWindow);
        }
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