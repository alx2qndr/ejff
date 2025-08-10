#include "ejff/gpu/resources/texture.hpp"
#include "ejff/gpu/device.hpp"

#include <stdexcept>

#include <fmt/format.h>

namespace ejff::gpu
{

Texture::Texture(Device &device, TextureType type, TextureFormat format,
                 TextureUsageFlags usage, uint32_t width, uint32_t height,
                 uint32_t layerCountOrDepth, uint32_t numLevels,
                 SampleCount sampleCount)
    : ptr_(create(device, type, format, usage, width, height, layerCountOrDepth,
                  numLevels, sampleCount),
           SDL_GPUTextureDeleter{device.get()})
{
}

SDL_GPUTexture *Texture::create(Device &device, TextureType type,
                                TextureFormat format, TextureUsageFlags usage,
                                uint32_t width, uint32_t height,
                                uint32_t layerCountOrDepth, uint32_t numLevels,
                                SampleCount sampleCount)
{
    SDL_GPUTextureCreateInfo createInfo{};
    createInfo.type = static_cast<SDL_GPUTextureType>(type);
    createInfo.format = static_cast<SDL_GPUTextureFormat>(format);
    createInfo.usage = static_cast<SDL_GPUTextureUsageFlags>(usage);
    createInfo.width = static_cast<Uint32>(width);
    createInfo.height = static_cast<Uint32>(height);
    createInfo.layer_count_or_depth = static_cast<Uint32>(layerCountOrDepth);
    createInfo.num_levels = static_cast<Uint32>(numLevels);
    createInfo.sample_count = static_cast<SDL_GPUSampleCount>(sampleCount);

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