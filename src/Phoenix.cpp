#include "glad/glad.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <Phoenix.hpp>
#include <cstdio>
#include <cstdlib>
#include <gfx/Renderer2D.hpp>
#include <gfx/Shader.hpp>
#include <string>

namespace phnx {
void Init() {
    printf("Initializing GLFW %d.%d\n", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR);
    if (!glfwInit()) {
        printf("Failed To Initialize GLFW...\n");
        exit(1);
    };
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

int main() {
    phnx::Init();
    phnx::Window w = phnx::Window(1080, 720, "Test Window");

    phnx::InitOpenGL(w);

    phnx::gfx::Shader *shader = phnx::gfx::Shader::Load(
        "res/shaders/simple.vs", "res/shaders/simple.frag");

    shader->Bind();

    while (w.IsOpen()) {
        phnx::PollEvents();
        phnx::gfx::Clear(0.1, 0.2, 0.3, 1.0);
        phnx::gfx::PushVertex({0.0, 1.0, 0.0}, {1.0, 1.0, 1.0}, {0.5, 1.0});
        phnx::gfx::PushVertex({1.0, -1.0, 0.0}, {1.0, 1.0, 1.0}, {1.0, 0.0});
        phnx::gfx::PushVertex({-1.0, -1.0, 0.0}, {1.0, 1.0, 1.0}, {0.0, 0.0});
        phnx::gfx::Flush();
        w.SwapBuffers();
    }
}
