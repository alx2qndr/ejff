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
    explicit Surface(const std::filesystem::path &path);

    Surface(const Surface &) = delete;
    Surface &operator=(const Surface &) = delete;

    Surface(Surface &&) noexcept = default;
    Surface &operator=(Surface &&) noexcept = default;

    ~Surface() = default;

    void convert(SDL_PixelFormat format);

    void flip(SDL_FlipMode flipMode);

    SDL_Surface *get() const noexcept { return ptr_.get(); }

private:
    SDL_Surface *create(int width, int height, SDL_PixelFormat format);
    SDL_Surface *loadSurfaceFromPath(const std::filesystem::path &path);

    std::unique_ptr<SDL_Surface, SDL_SurfaceDeleter> ptr_{nullptr};
};

} // namespace ejff
