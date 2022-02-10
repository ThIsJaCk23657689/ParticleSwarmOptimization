#ifndef UI_HPP
#define UI_HPP

#include <SDL.h>
#include <imgui.h>

#include <string>

struct UI {
    UI(SDL_Window* window, SDL_GLContext gl_context);

    SDL_Window* WindowHandler;
    SDL_GLContext GLContext;
    bool WantCaptureEvent = false;

    struct Windows {
        struct About {
            bool Visible = false;
            int WindowFlags = 0;
            ImVec2 ChildSize = ImVec2(350, 300);
        } About;
#ifndef NDEBUG
        struct Demo {
            bool Visible = false;
        } Demo;
#endif
    } Windows;

    void Create();
    void Destroy();
    void Render();
    void ProcessEvent(const SDL_Event &event);

private:
    void MenuBarRender();
    void WindowsRender();
};

#endif