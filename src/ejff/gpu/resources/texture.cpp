#include "ejff/gpu/resources/texture.hpp"
#include "ejff/gpu/device.hpp"

#include <stdexcept>

#include <fmt/format.h>

namespace ejff::gpu
{

Texture::Texture(Device &device, SDL_GPUTextureType type,
                 gpu::TextureFormat format, SDL_GPUTextureUsageFlags usage,
                 uint32_t width, uint32_t height, uint32_t layerCountOrDepth,
                 uint32_t numLevels, SDL_GPUSampleCount sampleCount)
    : ptr_(create(device, type, format, usage, width, height, layerCountOrDepth,
                  numLevels, sampleCount),
           SDL_GPUTextureDeleter{device.get()})
{
}

SDL_GPUTexture *Texture::create(Device &device, SDL_GPUTextureType type,
                                gpu::TextureFormat format,
                                SDL_GPUTextureUsageFlags usage, uint32_t width,
                                uint32_t height, uint32_t layerCountOrDepth,
                                uint32_t numLevels,
                                SDL_GPUSampleCount sampleCount)
{
    SDL_GPUTextureCreateInfo createInfo{};
    createInfo.type = type;
    createInfo.format = static_cast<SDL_GPUTextureFormat>(format);
    createInfo.usage = usage;
    createInfo.width = static_cast<Uint32>(width);
    createInfo.height = static_cast<Uint32>(height);
    createInfo.layer_count_or_depth = static_cast<Uint32>(layerCountOrDepth);
    createInfo.num_levels = static_cast<Uint32>(numLevels);
    createInfo.sample_count = sampleCount;

    auto texture = SDL_CreateGPUTexture(device.get(), &createInfo);
    if (!texture)
    {
        throw std::runtime_error(fmt::format("Couldn't create SDL_GPUTexture. "
                                             "SDL_CreateGPUTexture failed: {}",
                                             SDL_GetError()));
    }

    return texture;
}

} // namespace ejff::gpu