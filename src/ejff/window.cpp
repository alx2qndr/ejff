#include "ejff/window.hpp"

#include <stdexcept>

#include <fmt/format.h>

namespace ejff
{

Window::Window(std::string_view title, int width, int height, SDL_WindowFlags flags)
    : ptr_(nullptr, SDL_WindowDeleter{})
{
    auto window = SDL_CreateWindow(title.data(), width, height, flags);
    if (!window)
    {
        throw std::runtime_error(fmt::format(
            "Couldn't create SDL_Window. SDL_CreateWindow failed: {}", SDL_GetError()));
    }

    ptr_.reset(window);
}

} // namespace ejff