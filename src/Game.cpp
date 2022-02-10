#include "Game.hpp"

#include "State.hpp"

Game::Game() {
    // TODO:: Create Shader
    basic_shader = std::make_unique<Shader>("assets/shaders/basic.vert", "assets/shaders/basic.frag");

    // TODO:: Model Matrix Stack

    // TODO:: Build a world (Entity, Camera, Geometry)
    state.world = std::make_unique<World>();
    state.world->create();
}

void Game::Update(float dt) {

}

void Game::Render(float dt) {
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), state.window->width / static_cast<float>(state.window->height), 0.1f, 500.0f);

    basic_shader->Use();
    basic_shader->SetMat4("view", view);
    basic_shader->SetMat4("projection", projection);

    basic_shader->SetVec3("objectColor", glm::vec3(0.2f, 0.4f, 0.12f));
    basic_shader->SetMat4("model", glm::mat4(1.0f));
    state.world->my_triangle->Draw();
}

void Game::HandleEvents() {
    // 將所有事件拉出來到 vector 中
    PollEvents();

    // 透過迴圈一個一個去跑 vector 來跑事件處理
    for (auto it = std::cbegin(events); it != std::cend(events); it++) {
        // 先處理 ImGui 的事件
        state.ui->ProcessEvent(*it);

        // 再來處理 SDL 自己的事件
        ProcessEvents(*it, state.ui->WantCaptureEvent);
    }

    // 如果 ImGui 佔用了滑鼠與鍵盤時，就不會執行下面的事件控制
    if (state.ui->WantCaptureEvent) {
        return;
    }

    // 執行攝影機的控制，這邊事件觸發並不是透過 SDL_Event ，而是透過像是 SDL_GetKeyboardState() 和 SDL_GetRelativeMouseState() 去控制的。
    // Camera Event Handler
    // TODO: Camera Control
}

void Game::PollEvents() {
    events.clear();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        events.push_back(event);
    }
}

void Game::ProcessEvents(const SDL_Event &event, bool ByPassSceneEvents) {
    // 優先度大於 ImGui 的事件：離開程式
    GlobalEvents(event);

    if (ByPassSceneEvents) {
        return;
    }

    // 優先度小於 ImGui
    SceneEvents(event);
}

void Game::GlobalEvents(const SDL_Event &event) {
    switch (event.type) {
        case SDL_QUIT:
            state.window->should_close = true;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_q) {
                if (event.key.keysym.mod & KMOD_CTRL) {
                    state.window->should_close = true;
                }
            }
            if (event.key.keysym.sym == SDLK_TAB) {
                // TODO: Toggle Camera Control
            }
            break;
        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                // 更新視窗長寬
                SDL_GetWindowSize(state.window->handler, &state.window->width, &state.window->height);
            }
            break;
    }
}

void Game::SceneEvents(const SDL_Event &event) {
    switch (event.type) {
        case SDL_KEYDOWN:
            OnKeyDownEvent(event.key);
            break;
        case SDL_MOUSEBUTTONDOWN:
            OnMouseButtonEvent(event.button);
            break;
        case SDL_MOUSEMOTION:
            OnMouseMotionEvent(event.motion);
            break;
        case SDL_MOUSEWHEEL:
            OnMouseWheelEvent(event.wheel);
            break;
        case SDL_WINDOWEVENT:
            OnWindowEvent(event.window);
            break;
    }
}

void Game::OnKeyDownEvent(const SDL_KeyboardEvent& e) {
//    switch (e.keysym.sym) {
//        default:
//            break;
//    }
}

void Game::OnMouseButtonEvent(const SDL_MouseButtonEvent& e) {
    switch (e.button) {
        case SDL_BUTTON_LEFT:
            break;
        case SDL_BUTTON_MIDDLE:
            break;
        case SDL_BUTTON_RIGHT:
            break;
    }
}

void Game::OnMouseMotionEvent(const SDL_MouseMotionEvent& e) {
    switch (e.state) {
        case SDL_BUTTON_LMASK:
            break;
        case SDL_BUTTON_RMASK:
            break;
        default:
            break;
    }
}

void Game::OnMouseWheelEvent(const SDL_MouseWheelEvent& e) {
}

void Game::OnWindowEvent(const SDL_WindowEvent& e) {
//    switch (e.event) {
//        default:
//            break;
//    }
}