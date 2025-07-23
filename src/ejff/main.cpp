#include "ejff/application.hpp"

#include <iostream>
#include <stdexcept>

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <fmt/format.h>

struct AppState
{
    ejff::Application app;
};

SDL_AppResult SDL_AppInit(void **appstate, [[maybe_unused]] int argc, [[maybe_unused]] char **argv)
{
    try
    {
        if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO))
        {
            throw std::runtime_error(
                fmt::format("Couldn't initialize SDL. SDL_Init failed: {}", SDL_GetError()));
        }

        auto *state = new AppState();
        *appstate = state;
    }
    catch (const std::exception &e)
    {
        std::cerr << fmt::format("Couldn't initialize application. Thrown exception: {}\n",
                                 e.what());
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    auto *state = static_cast<AppState *>(appstate);
    if (!state)
    {
        return SDL_APP_FAILURE;
    }

    try
    {
        state->app.iterate();
    }
    catch (const std::exception &e)
    {
        std::cerr << fmt::format("Couldn't iterate application. Thrown exception: {}\n", e.what());
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    auto *state = static_cast<AppState *>(appstate);
    return state->app.event(*event);
}

void SDL_AppQuit(void *appstate, [[maybe_unused]] SDL_AppResult result)
{
    auto *state = static_cast<AppState *>(appstate);
    if (state)
    {
        try
        {
            delete state;
        }
        catch (const std::exception &e)
        {
            std::cerr << fmt::format("Couldn't quit application. Thrown exception: {}\n", e.what());
        }
    }

    SDL_Quit();
}
