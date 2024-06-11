#pragma once
#include "Phoenix/gfx/vk/Vulkan.hpp"
#include "glm/ext/vector_int2.hpp"
#include <Phoenix.hpp>
#include <string>
namespace phnx {

    struct WindowSpec {
        int Width = 640, Height = 480;
        std::string Title = "Phoenix App";
        bool Vsync = true;
    };

    class Application2D {
    public:
        virtual bool OnCreate() = 0;
        virtual bool OnUpdate() = 0;
        virtual void OnRender() = 0;
        virtual void OnDestroy() = 0;
        virtual void OnImGui() = 0;
        virtual WindowSpec WindowSpecs() = 0;


        void Start();
    private:
        Window* mWindow;
        VK::Context* mContext;
    }; 
}