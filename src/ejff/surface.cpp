#include "ejff/surface.hpp"

#include <stdexcept>

#include <SDL3_image/SDL_image.h>

#include <fmt/format.h>

namespace ejff
{

Surface::Surface(int width, int height, SDL_PixelFormat format)
    : ptr_(nullptr, SDL_SurfaceDeleter{})
{
    auto surface = SDL_CreateSurface(width, height, format);
    if (!surface)
    {
        throw std::runtime_error(fmt::format(
            "Couldn't create SDL_Surface. SDL_CreateSurface failed: {}", SDL_GetError()));
    }

    ptr_.reset(surface);
}

Surface::Surface(SDL_Surface *surface) : ptr_(surface, SDL_SurfaceDeleter{}) {}

Surface Surface::load_image(const std::filesystem::path &path)
{
    auto surface = IMG_Load(path.string().c_str());
    if (!surface)
    {
        throw std::runtime_error(fmt::format(
            "Couldn't load SDL_Surface from image. IMG_Load failed: {}", SDL_GetError()));
    }
    return Surface(surface);
}

void Surface::convert(SDL_PixelFormat format)
{
    auto surface = SDL_ConvertSurface(ptr_.get(), format);
    if (!surface)
    {
        throw std::runtime_error(fmt::format(
            "Couldn't convert SDL_Surface. SDL_ConvertSurface failed: {}", SDL_GetError()));
    }

    ptr_.reset(surface);
}

} // namespace ejff