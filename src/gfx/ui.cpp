#include "imgui.h"
#include "misc/freetype/imgui_freetype.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <Phoenix/gfx/ui.hpp>

namespace phnx {
namespace ui {
void Init(GLFWwindow *window) {
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 410 core");

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImFontConfig config = {};
    config;



    io.Fonts->FontBuilderIO = ImGuiFreeType::GetBuilderForFreeType();
    io.FontDefault = io.Fonts->AddFontFromFileTTF("res/fonts/FiracodeNerd.ttf", 16);
    ImVec4* colors = ImGui::GetStyle().Colors;

    colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg]               = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
    colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg]                = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    colors[ImGuiCol_Border]                 = ImVec4(0.43f, 0.43f, 0.43f, 0.50f);
    colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg]                = ImVec4(0.27f, 0.27f, 0.27f, 0.55f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.41f, 0.41f, 0.41f, 0.54f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(0.55f, 0.55f, 0.55f, 0.54f);
    colors[ImGuiCol_TitleBg]                = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
    colors[ImGuiCol_TitleBgActive]          = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_CheckMark]              = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_SliderGrab]             = ImVec4(0.64f, 0.64f, 0.64f, 1.00f);
    colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.92f, 0.92f, 0.92f, 1.00f);
    colors[ImGuiCol_Button]                 = ImVec4(0.64f, 0.64f, 0.64f, 0.40f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(0.73f, 0.72f, 0.72f, 0.40f);
    colors[ImGuiCol_ButtonActive]           = ImVec4(0.92f, 0.92f, 0.92f, 0.40f);
    colors[ImGuiCol_Header]                 = ImVec4(0.47f, 0.55f, 0.65f, 0.31f);
    colors[ImGuiCol_HeaderHovered]          = ImVec4(0.64f, 0.69f, 0.76f, 0.31f);
    colors[ImGuiCol_HeaderActive]           = ImVec4(0.61f, 0.75f, 0.92f, 0.31f);
    colors[ImGuiCol_Separator]              = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.37f, 0.42f, 0.49f, 0.78f);
    colors[ImGuiCol_SeparatorActive]        = ImVec4(0.53f, 0.65f, 0.79f, 1.00f);
    colors[ImGuiCol_ResizeGrip]             = ImVec4(0.61f, 0.61f, 0.61f, 0.20f);
    colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.64f, 0.64f, 0.64f, 0.20f);
    colors[ImGuiCol_ResizeGripActive]       = ImVec4(1.00f, 1.00f, 1.00f, 0.20f);
    colors[ImGuiCol_Tab]                    = ImVec4(0.23f, 0.23f, 0.23f, 0.86f);
    colors[ImGuiCol_TabHovered]             = ImVec4(0.35f, 0.34f, 0.34f, 0.86f);
    colors[ImGuiCol_TabActive]              = ImVec4(0.52f, 0.52f, 0.52f, 0.86f);
    colors[ImGuiCol_TabUnfocused]           = ImVec4(0.15f, 0.15f, 0.15f, 0.86f);
    colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
    colors[ImGuiCol_DockingPreview]         = ImVec4(0.77f, 0.77f, 0.77f, 0.70f);
    colors[ImGuiCol_DockingEmptyBg]         = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
    colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_TableBorderLight]       = ImVec4(0.42f, 0.42f, 0.42f, 1.00f);
    colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_TableRowBgAlt]          = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
    colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.56f, 0.56f, 0.56f, 0.35f);
    colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
    colors[ImGuiCol_NavHighlight]           = ImVec4(0.61f, 0.79f, 1.00f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

    ImGui::GetStyle().FrameRounding = 4;

}

void BeginFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}
void EndFrame() {
    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Dockspace() {
    ImGui::DockSpaceOverViewport();
}
} // namespace ui
} // namespace phnx
