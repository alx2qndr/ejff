#include "ejff/surface.hpp"

#include <stdexcept>

#include <SDL3_image/SDL_image.h>

#include <fmt/format.h>

namespace ejff
{

Surface::Surface(int width, int height, SDL_PixelFormat format)
    : ptr_(create(width, height, format), SDL_SurfaceDeleter{})
{
}

Surface::Surface(const std::filesystem::path &path)
    : ptr_(createFromImage(path), SDL_SurfaceDeleter{})
{
}

void Surface::flip(SDL_FlipMode flipMode)
{
    if (!SDL_FlipSurface(ptr_.get(), flipMode))
    {
        throw std::runtime_error(
            fmt::format("Couldn't flip SDL_Surface. SDL_FlipSurface failed: {}",
                        SDL_GetError()));
    }
}

void Surface::convert(SDL_PixelFormat format)
{
    auto surface = SDL_ConvertSurface(ptr_.get(), format);
    if (!surface)
    {
        throw std::runtime_error(fmt::format(
            "Couldn't convert SDL_Surface. SDL_ConvertSurface failed: {}",
            SDL_GetError()));
    }

    ptr_.reset(surface);
}

SDL_Surface *Surface::create(int width, int height, SDL_PixelFormat format)
{
    auto surface = SDL_CreateSurface(width, height, format);
    if (!surface)
    {
        throw std::runtime_error(fmt::format(
            "Couldn't create SDL_Surface. SDL_CreateSurface failed: {}",
            SDL_GetError()));
    }
    return surface;
}

SDL_Surface *Surface::createFromImage(const std::filesystem::path &path)
{
    auto surface = IMG_Load(path.string().c_str());
    if (!surface)
    {
        throw std::runtime_error(fmt::format(
            "Couldn't create SDL_Surface. SDL_CreateSurface failed: {}",
            SDL_GetError()));
    }
    return surface;
}

} // namespace ejff