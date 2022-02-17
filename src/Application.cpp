#include "Application.hpp"

#include <SDL.h>
#include <glad/glad.h>

#include "UI.hpp"
#include "Window.hpp"
#include "Util/Logger.hpp"

#include "State.hpp"

Application::Application(const Config& config) : my_config(config) {
    Initialize();
}

Application::~Application() {
    state.ui->Destroy();
    SDL_GL_DeleteContext(state.context);
    SDL_DestroyWindow(state.window->handler);
    SDL_Quit();
}

void Application::Initialize() {
    Logger::ShowMe();

    // Initialize SDL2
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        Logger::Message(LogLevel::SDLError, "Oops! Failed to initialize SDL2. :(");
        exit(-1);
    }
    Logger::Message(LogLevel::Info, "Initialize SDL2 successfully.");

    // Request an OpenGL 3.3 context and setting "Core" mode
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, my_config.opengl_major_version);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, my_config.opengl_minor_version);
#ifdef __APPLE__
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
#endif
#ifdef __linux__
    SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0");
#endif

    // Anti-aliasing
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

    // Other Settings
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    // Create a window
    state.window = std::make_unique<Window>();
    if (my_config.is_fullscreen) {
        const auto flags = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_ALLOW_HIGHDPI;
        state.window->handler = SDL_CreateWindow(my_config.title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                              0, 0, flags);
    } else {
        const auto flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI;
        state.window->handler = SDL_CreateWindow(my_config.title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                              my_config.width, my_config.height, flags);
    }
    if (state.window->handler == nullptr) {
        Logger::Message(LogLevel::SDLError, "Failed to create SDL2 window: ");
        exit(-1);
    }
    SDL_SetWindowMinimumSize(state.window->handler, 400, 300);

    // Create a OpenGL context
    state.context = SDL_GL_CreateContext(state.window->handler);
    if (state.context == NULL) {
        Logger::Message(LogLevel::SDLError, "Failed to create OpenGL context with SDL2 window: ");
        exit(-1);
    }
    SDL_GL_MakeCurrent(state.window->handler, state.context);
    Logger::Message(LogLevel::Info, "Create OpenGL context successfully.");

    // This make our buffers swap synchronized with the monitor's vertical refresh
    SDL_GL_SetSwapInterval(1);

    // Setting the mouse mode
    SDL_SetHintWithPriority(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1", SDL_HINT_OVERRIDE);

    // Initialize GLAD (Must behind the create window)
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        Logger::Message(LogLevel::Error, "Failed to initialize GLAD.");
        exit(-1);
    }
    Logger::Message(LogLevel::Info, "Initialize GLAD successfully.");

    // OpenGL basic settings
    SDL_GetWindowSize(state.window->handler, &state.window->width, &state.window->height);
    glViewport(0, 0, state.window->width, state.window->height);

    // 輸出訊息
    Logger::ShowGLInfo();

    // 設定 gl
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    state.ui = std::make_unique<UI>(state.window->handler, state.context);

    game = std::make_unique<Game>();
}

void Application::Run() {
    while (!state.window->should_close) {
        current_time = static_cast<float>(SDL_GetTicks()) / 1000.0f;
        delta_time = current_time - last_time;
        last_time = current_time;

        game->HandleEvents();

        game->Update(delta_time);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        game->Render(delta_time);

        state.ui->Render();

        SDL_GL_SwapWindow(state.window->handler);
    }
    Logger::Message(LogLevel::Info, "Good Bye :)");
}