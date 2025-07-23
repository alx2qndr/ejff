#pragma once

#include <memory>
#include <string_view>

#include <SDL3/SDL.h>

namespace ejff
{

struct SDL_WindowDeleter
{
    void operator()(SDL_Window *window) const noexcept
    {
        if (window)
        {
            SDL_DestroyWindow(window);
        }
    }
};

class Window
{
public:
    Window() = default;

    explicit Window(std::string_view title, int width, int height, SDL_WindowFlags flags);

    Window(const Window &) = delete;
    Window &operator=(const Window &) = delete;

    Window(Window &&) noexcept = default;
    Window &operator=(Window &&) noexcept = default;

    ~Window() = default;

    void reset(SDL_Window *new_window = nullptr) noexcept { ptr_.reset(new_window); }

    SDL_Window *release() noexcept { return ptr_.release(); }

    explicit operator bool() const noexcept { return ptr_ != nullptr; }

    SDL_Window *get() noexcept { return ptr_.get(); }
    SDL_Window *get() const noexcept { return ptr_.get(); }

private:
    std::unique_ptr<SDL_Window, SDL_WindowDeleter> ptr_;
};

} // namespace ejff
