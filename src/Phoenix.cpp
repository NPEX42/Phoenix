#include "gfx/Texture.hpp"
#include "glad/glad.h"
#include "glm/ext/vector_float2.hpp"
#include "imgui.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <Phoenix.hpp>
#include <cstdio>
#include <cstdlib>
#include <gfx/Renderer2D.hpp>
#include <gfx/Shader.hpp>
#include <gfx/ui.hpp>
#include <memory>
#include <string>
#include <vector>

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
    phnx::Window w = phnx::Window(1080, 720, "Test Window");

    phnx::InitOpenGL(w);

    phnx::ui::Init((GLFWwindow *)w.Handle());

    phnx::gfx::Shader *shader = phnx::gfx::Shader::Load("res/shaders/simple.vs", "res/shaders/simple.frag");

    shader->Bind();

    std::shared_ptr<phnx::gfx::Texture2D> snom = phnx::gfx::LoadTexture2D("res/textures/snom.png", true);

    shader->SetInt("uAlbedo", 1);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glm::vec2 quad_size = {5, 0};
    int max_snoms = 0;

    std::vector<glm::vec2> snom_positions;
    snom_positions.resize(max_snoms);
    for (int i = 0; i < max_snoms; i++) {
        snom_positions[i] = {RandFloat(1080), RandFloat(720)};
    }
    double start = ImGui::GetTime(), end = start, deltaTime;

    phnx::gfx::SetFrameSize(1080, 720);
    bool enableBlend = true;

    phnx::gfx::SetAlbedo(snom);

    while (w.IsOpen()) {
        start = ImGui::GetTime();
        phnx::PollEvents();

        phnx::gfx::Clear(0.1, 0.2, 0.3, 1.0);
        double draw_start = glfwGetTime();
        for (glm::vec2 &pos : snom_positions) {
            phnx::gfx::Quad(pos, snom->Size() / quad_size.x, {1, 1, 1});
        }
        double draw_end = glfwGetTime();
        double draw_time = draw_end - draw_start;
        phnx::gfx::Flush();

        phnx::ui::BeginFrame();
        ImGui::Begin("Window");

        ImGui::Text("DeltaTime: %03.2f ms - %02.2f fps", (deltaTime * 1000.0f), 1.0f / deltaTime);
        ImGui::Text("Draw Loop Time: %03.2f ms (%03.2f us/Snom)", (draw_time * 1000.0f),
                    (draw_time / max_snoms) * 10000000.0f);

        ImGui::Separator();

        // if (ImGui::InputInt("Max Snom", &max_snoms)) {
        //     if (max_snoms < 1) {
        //         max_snoms = 1;
        //     }
        //

        if (deltaTime < 0.0167) {
            for (int i = 0; i < 128; i++) {
                snom_positions.push_back({RandFloat(1080), RandFloat(720)});
                max_snoms += 1;
            }
        }

        ImGui::Text("Snoms: %d - Snoms / Second: %d", max_snoms, (int)(max_snoms / deltaTime));
        ImGui::Text("Batches: %d", phnx::gfx::BatchCount());
        //}

        ImGui::SliderFloat("Snom Scale Div.", &quad_size.x, 1.0f, 100.0f);

        if (ImGui::Checkbox("Alpha Blending", &enableBlend)) {
            if (enableBlend) {
                glEnable(GL_BLEND);
            } else {
                glDisable(GL_BLEND);
            }
        }

        ImGui::End();
        phnx::ui::EndFrame();
        end = ImGui::GetTime();
        deltaTime = (end - start);
        w.SwapBuffers();

        phnx::gfx::ResetStats();
    }
}
