#include "Phoenix/Application2D.hpp"
#include "Phoenix/AssetManager.hpp"
#include "Phoenix/Log.hpp"
#include "Phoenix/Util.hpp"
#include "Phoenix/gfx/Renderer2D.hpp"
#include <Phoenix/gfx/ui.hpp>
#include "Phoenix/gfx/Shader.hpp"
#include "Phoenix/gfx/Texture.hpp"
#include "Phoenix/gfx/TextureAtlas.hpp"
#include "fmt/core.h"
#include "glad/glad.h"
#include "glm/ext/vector_float2.hpp"
#include "imgui.h"
#include "nfd.h"
#include "yaml-cpp/node/node.h"
#include <Phoenix.hpp>
#include <algorithm>
#include <cstddef>
#include <cstring>
#include <memory>
#include <string>

#include <nfd.hpp>
#include <string_view>

class Sandbox : public phnx::Application2D {

   

    bool OnCreate() override {


        

        return true;
    }

    bool OnUpdate() override {
        return true;
    }

    void OnRender() override {

    }

    void OnDestroy() override {

    }

    void OnImGui() override {
        
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