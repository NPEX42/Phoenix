#include "Phoenix/Application2D.hpp"
#include "Phoenix/gfx/Texture.hpp"
#include "glad/glad.h"
#include "glm/ext/vector_float2.hpp"
#include "imgui.h"
#include <GLFW/glfw3.h>
#include <Phoenix.hpp>
#include <cstdio>
#include <cstdlib>
#include <Phoenix/gfx/Renderer2D.hpp>
#include <Phoenix/gfx/Shader.hpp>
#include <Phoenix/gfx/ui.hpp>
#include <memory>
#include <string>
#include <vector>

extern phnx::Application2D* CreateApp();

namespace phnx {
void Init() {
    printf("Initializing GLFW %d.%d\n", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR);
    if (!glfwInit()) {
        printf("Failed To Initialize GLFW...\n");
        exit(1);
    };

    // L = luaL_newstate();
}

void PollEvents() { glfwPollEvents(); }

void InitOpenGL(Window &w) {
    glfwMakeContextCurrent((GLFWwindow *)w.Handle());
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed To Load OpenGL\n");
        exit(2);
    }

    printf("Loaded OpenGL v%s\n", glGetString(GL_VERSION));

    phnx::gfx::Init();
}

Window::Window(int width, int height, std::string title) : mWindow(nullptr) {
    mWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
}

bool Window::IsOpen() { return !glfwWindowShouldClose(mWindow); }
void Window::SwapBuffers() { glfwSwapBuffers(mWindow); }
} // namespace phnx

float RandFloat(float max) {
    float x = rand() / (float)RAND_MAX;
    return (float)x * max;
}

int main() {
    phnx::Init();
    phnx::Application2D* app = CreateApp();
    if (app)
        app->Start();
}
