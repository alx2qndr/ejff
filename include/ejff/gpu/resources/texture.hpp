#pragma once

#include "ejff/gpu/enums/sample_count.hpp"
#include "ejff/gpu/enums/texture_format.hpp"
#include "ejff/gpu/enums/texture_type.hpp"
#include "ejff/gpu/enums/texture_usage_flags.hpp"

#include <memory>

#include <SDL3/SDL.h>

namespace ejff::gpu
{

class Device;

struct SDL_GPUTextureDeleter
{
    SDL_GPUDevice *device;

    SDL_GPUTextureDeleter(SDL_GPUDevice *device = nullptr) : device(device) {}

    void operator()(SDL_GPUTexture *texture) const noexcept
    {
        if (texture)
        {
            SDL_ReleaseGPUTexture(device, texture);
        }
    }
};

class Texture
{
public:
    Texture() = default;

    explicit Texture(Device &device, TextureType type, TextureFormat format,
                     TextureUsageFlags usage, uint32_t width, uint32_t height,
                     uint32_t layerCountOrDepth, uint32_t numLevels,
                     SampleCount sampleCount);

    Texture(const Texture &) = delete;
    Texture &operator=(const Texture &) = delete;

    Texture(Texture &&) noexcept = default;
    Texture &operator=(Texture &&) noexcept = default;

    ~Texture() = default;

    SDL_GPUTexture *get() const noexcept { return ptr_.get(); }

private:
    SDL_GPUTexture *create(Device &device, TextureType type,
                           TextureFormat format, TextureUsageFlags usage,
                           uint32_t width, uint32_t height,
                           uint32_t layerCountOrDepth, uint32_t numLevels,
                           SampleCount sampleCount);

    std::unique_ptr<SDL_GPUTexture, SDL_GPUTextureDeleter> ptr_{nullptr};
};

} // namespace ejff::gpu