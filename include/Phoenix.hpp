#pragma once

#include <cstdint>
#include <cstdio>
#include <string>
#ifdef PLATFORM_LINUX
#include <unistd.h>
#endif

typedef struct GLFWwindow GLFWwindow;

namespace phnx {
void Init();
void PollEvents();

class Window {
public:
    int Height();
    int Width();

    Window(int width, int height, std::string title);

    bool IsOpen();
    void SwapBuffers();

    void *Handle() { return mWindow; }

private:
    GLFWwindow *mWindow;
};

void InitOpenGL(Window &w);

} // namespace phnx
