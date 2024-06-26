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
#include <iostream>
#include <memory>
#include <string>
#include <vector>

extern phnx::Application2D* CreateApp();


void APIENTRY glDebugOutput(GLenum source, 
                            GLenum type, 
                            unsigned int id, 
                            GLenum severity, 
                            GLsizei length, 
                            const char *message, 
                            const void *userParam)
{
    // ignore non-significant error/warning codes
    if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return; 

    std::cout << "---------------" << std::endl;
    std::cout << "Debug message (" << id << "): " <<  message << std::endl;

    switch (source)
    {
        case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
        case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
    } std::cout << std::endl;

    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break; 
        case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
        case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
    } std::cout << std::endl;
    
    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
        case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
    } std::cout << std::endl;
    std::cout << std::endl;
}

namespace phnx {
void Init() {
    printf("Initializing GLFW %d.%d\n", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR);
    if (!glfwInit()) {
        printf("Failed To Initialize GLFW...\n");
        exit(1);
    };

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);  


    

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

    int flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
         glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); 
        glDebugMessageCallback(glDebugOutput, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }

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
