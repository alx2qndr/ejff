#pragma once

#include "ejff/utilities/enable_bit_mask_operators.hpp"

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

#include <cstdint>

class Window
{
public:
    enum class Flags : uint64_t
    {
        eFullscreen = SDL_WINDOW_FULLSCREEN,
        eOpengl = SDL_WINDOW_OPENGL,
        eOccluded = SDL_WINDOW_OCCLUDED,
        eHidden = SDL_WINDOW_HIDDEN,
        eBorderless = SDL_WINDOW_BORDERLESS,
        eResizable = SDL_WINDOW_RESIZABLE,
        eMinimized = SDL_WINDOW_MINIMIZED,
        eMaximized = SDL_WINDOW_MAXIMIZED,
        eMousegrabbed = SDL_WINDOW_MOUSE_GRABBED,
        eInputfocus = SDL_WINDOW_INPUT_FOCUS,
        eMousefocus = SDL_WINDOW_MOUSE_FOCUS,
        eExternal = SDL_WINDOW_EXTERNAL,
        eModal = SDL_WINDOW_MODAL,
        eHighPixelDensity = SDL_WINDOW_HIGH_PIXEL_DENSITY,
        eMousecapture = SDL_WINDOW_MOUSE_CAPTURE,
        eMouserelativemode = SDL_WINDOW_MOUSE_RELATIVE_MODE,
        eAlwaysontop = SDL_WINDOW_ALWAYS_ON_TOP,
        eUtility = SDL_WINDOW_UTILITY,
        eTooltip = SDL_WINDOW_TOOLTIP,
        ePopupmenu = SDL_WINDOW_POPUP_MENU,
        eKeyboardgrabbed = SDL_WINDOW_KEYBOARD_GRABBED,
        eVulkan = SDL_WINDOW_VULKAN,
        eMetal = SDL_WINDOW_METAL,
        eTransparent = SDL_WINDOW_TRANSPARENT,
        eNotfocusable = SDL_WINDOW_NOT_FOCUSABLE
    };

    Window() = default;

    explicit Window(std::string_view title, int width, int height, Flags flags);

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

ENABLE_BITMASK_OPERATORS(ejff::Window::Flags)