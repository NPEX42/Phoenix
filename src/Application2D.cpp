#include "imgui.h"
#include "nfd.hpp"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include <Phoenix/Application2D.hpp>
#include <Phoenix/gfx/ui.hpp>



namespace phnx {
    void Application2D::Start() {

        WindowSpec spec = WindowSpecs();

        mWindow = new Window(spec.Width, spec.Height, spec.Title);

        glfwSwapInterval(spec.Vsync ? 1 : 0);

        InitOpenGL(*mWindow);

        ui::Init((GLFWwindow *)mWindow->Handle());

        NFD::Init();

        if (!OnCreate()) {
            return;
        }

        
        
        while (mWindow->IsOpen()) {
            mFrameStart = glfwGetTime();
            PollEvents();
            if (!OnUpdate()) {
                break;
            }
            OnRender();
            ui::BeginFrame();

            if (ImGui::BeginMainMenuBar()) {
                OnImGuiMainMenu();
                ImGui::EndMainMenuBar();
            }
            OnImGui();
            ui::EndFrame();
            
            mWindow->SwapBuffers();
            mDeltaTime = glfwGetTime() - mFrameStart;
        }
        
        OnDestroy();
    }

    void Application2D::OnImGuiMainMenu() {}
}