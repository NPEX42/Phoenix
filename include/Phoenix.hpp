#pragma once
#include <cstdio>
#include <string>
#ifdef PLATFORM_LINUX
#include <unistd.h>
#endif

typedef struct GLFWwindow GLFWwindow;

namespace phnx {
void Init();
void PollEvents();

enum Renderer {
    OpenGL, 
    Vulkan,
};

class Window {
public:
    int Height();
    int Width();

    Window(int width, int height, std::string title, Renderer renderer = Renderer::Vulkan);

    bool IsOpen();
    void SwapBuffers();

    void *Handle() { return mWindow; }

private:
    GLFWwindow *mWindow;
};

void InitOpenGL(Window &w);



} // namespace phnx
