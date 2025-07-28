#pragma once

#include <filesystem>
#include <memory>

#include <SDL3/SDL.h>

namespace ejff
{

struct SDL_SurfaceDeleter
{
    void operator()(SDL_Surface *surface) const noexcept
    {
        if (surface)
        {
            SDL_DestroySurface(surface);
        }
    }
};

class Surface
{
public:
    Surface() = default;

    explicit Surface(int width, int height, SDL_PixelFormat format);
    explicit Surface(SDL_Surface *surface);

    Surface(const Surface &) = delete;
    Surface &operator=(const Surface &) = delete;

    Surface(Surface &&) noexcept = default;
    Surface &operator=(Surface &&) noexcept = default;

    ~Surface() = default;

    static Surface load_image(const std::filesystem::path &path);

    void convert(SDL_PixelFormat format);

    void flip(SDL_FlipMode flip_mode);

    void reset(SDL_Surface *new_surface = nullptr) noexcept { ptr_.reset(new_surface); }

    SDL_Surface *release() noexcept { return ptr_.release(); }

    explicit operator bool() const noexcept { return ptr_ != nullptr; }

    SDL_Surface *get() noexcept { return ptr_.get(); }
    SDL_Surface *get() const noexcept { return ptr_.get(); }

private:
    std::unique_ptr<SDL_Surface, SDL_SurfaceDeleter> ptr_;
};

} // namespace ejff
