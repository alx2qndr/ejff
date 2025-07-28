#include "ejff/gpu/resources/texture.hpp"

#include <stdexcept>

#include <fmt/format.h>

namespace ejff::gpu
{

Texture::Texture(Device &device, SDL_GPUTextureType type, SDL_GPUTextureFormat format,
                 SDL_GPUTextureUsageFlags usage, Uint32 width, Uint32 height,
                 Uint32 layer_count_or_depth, Uint32 num_levels, SDL_GPUSampleCount sample_count)
    : ptr_(nullptr, SDL_GPUTextureDeleter{device.get()})
{
    SDL_GPUTextureCreateInfo createinfo{};
    createinfo.type = type;
    createinfo.format = format;
    createinfo.usage = usage;
    createinfo.width = width;
    createinfo.height = height;
    createinfo.layer_count_or_depth = layer_count_or_depth;
    createinfo.num_levels = num_levels;
    createinfo.sample_count = sample_count;

    auto texture = SDL_CreateGPUTexture(device.get(), &createinfo);
    if (!texture)
    {
        throw std::runtime_error(fmt::format("Couldn't create SDL_GPUTexture. "
                                             "SDL_CreateGPUTexture failed: {}",
                                             SDL_GetError()));
    }

    ptr_.reset(texture);
}

} // namespace ejff::gpu