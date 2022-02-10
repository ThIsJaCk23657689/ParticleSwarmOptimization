#ifndef GAME_HPP
#define GAME_HPP

#include <SDL.h>

#include <vector>
#include <memory>

#include "Shader/Shader.hpp"

struct Game {
    Game();

    void Update(float dt);
    void Render(float dt);

    void HandleEvents();

private:
    void PollEvents();
    void ProcessEvents(const SDL_Event &event, bool ByPassSceneEvents);
    void GlobalEvents(const SDL_Event &event);
    void SceneEvents(const SDL_Event &event);

    void OnKeyDownEvent(const SDL_KeyboardEvent& e);
    void OnMouseButtonEvent(const SDL_MouseButtonEvent& e);
    void OnMouseMotionEvent(const SDL_MouseMotionEvent& e);
    void OnMouseWheelEvent(const SDL_MouseWheelEvent& e);
    void OnWindowEvent(const SDL_WindowEvent& e);

    std::vector<SDL_Event> events = {};

    // TODO:: Make a Shader Manager to create
    std::unique_ptr<Shader> basic_shader = nullptr;
};

#endif
