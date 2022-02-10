#include "UI.hpp"

#include <glad/glad.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl.h>
#include <glm/gtc/type_ptr.hpp>

//#include "World.hpp"

UI::UI(SDL_Window* window, SDL_GLContext glContext) : WindowHandler(window), GLContext(glContext) {
    Create();
}

void UI::Create() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplSDL2_InitForOpenGL(WindowHandler, GLContext);
    ImGui_ImplOpenGL3_Init();
    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 5.0f;
    style.FrameRounding = 3.0f;
    style.FrameBorderSize = 1.0f;
}

void UI::Destroy() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void UI::Render() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(WindowHandler);
    ImGui::NewFrame();

    MenuBarRender();
    WindowsRender();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::ProcessEvent(const SDL_Event &event) {
    ImGui_ImplSDL2_ProcessEvent(&event);
    const ImGuiIO &io = ImGui::GetIO();
    WantCaptureEvent = io.WantCaptureKeyboard || io.WantCaptureMouse;
}

void UI::MenuBarRender() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("Edit##menubar-edit")) {
            // ImGui::MenuItem("Camera Info", nullptr, &Windows.CameraInfo.Visible);
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Help")) {
#ifndef NDEBUG
            if (ImGui::MenuItem("Dear ImGui Demo", nullptr)) {
                Windows.Demo.Visible = true;
            }
#endif

            if (ImGui::MenuItem("About", nullptr)) {
                Windows.About.Visible = true;
            }

            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void UI::WindowsRender() {
    Windows.About.WindowFlags = ImGuiWindowFlags_NoResize;

    // About Window Render
    if (Windows.About.Visible) {
        ImGui::Begin("About##Window_About", &Windows.About.Visible, Windows.About.WindowFlags);
        ImGui::SetWindowFontScale(1.2f);
        ImGui::Text("NTOU OpenGL Template - Camera");
        ImGui::SetWindowFontScale(1.0f);
        if (ImGui::BeginTabBar("TabBar##Window_About")) {
            if (ImGui::BeginTabItem("About##About")) {
                ImGui::BeginChild("Child##AboutAbout", Windows.About.ChildSize, true);
                ImGui::TextWrapped(
                        "An OpenGL template program for students learning Computer Graphics.\n"
                        "\n"
                        "Developed at:\n"
                        "National Taiwan Ocean University\n"
                        "\n"
                        "Copyright 2022, NTOU CSE 503 Authors\n");
                ImGui::EndChild();
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Components##About")) {
                ImGui::BeginChild("Child##AboutComponents", Windows.About.ChildSize, true);
                ImGui::Text(
                        "SDL2\n"
                        "Version %d.%d.%d\n"
                        "https://www.libsdl.org/\n",
                        SDL_MAJOR_VERSION,
                        SDL_MINOR_VERSION,
                        SDL_PATCHLEVEL);
                ImGui::Text(" ");
                ImGui::Separator();
                ImGui::Text("glad\nVersion 0.1.34\n");
                ImGui::Text(" ");
                ImGui::Separator();
                ImGui::Text("glm\nVersion 0.9.9.8\n");
                ImGui::Text(" ");
                ImGui::Separator();
                ImGui::Text(
                        "Dear ImGui\n"
                        "Version %s\n"
                        "https://github.com/ocornut/imgui\n",
                        IMGUI_VERSION);
                ImGui::EndChild();
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Authors##About")) {
                ImGui::BeginChild("Child##AboutAuthors", Windows.About.ChildSize, true);
                ImGui::Text("ThIsJaCk <y23657689@gmail.com>");
                ImGui::EndChild();
                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }
        ImGui::End();
    }

#ifndef NDEBUG
    // Demo Window Render
    if (Windows.Demo.Visible) {
        ImGui::ShowDemoWindow(&Windows.Demo.Visible);
    }
#endif
}