#pragma once

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

    explicit Texture(Device &device, SDL_GPUTextureType type,
                     SDL_GPUTextureFormat format,
                     SDL_GPUTextureUsageFlags usage, uint32_t width,
                     uint32_t height, uint32_t layerCountOrDepth,
                     uint32_t numLevels, SDL_GPUSampleCount sampleCount);

    Texture(const Texture &) = delete;
    Texture &operator=(const Texture &) = delete;

    Texture(Texture &&) noexcept = default;
    Texture &operator=(Texture &&) noexcept = default;

    ~Texture() = default;

    SDL_GPUTexture *get() const noexcept { return ptr_.get(); }

private:
    SDL_GPUTexture *create(Device &device, SDL_GPUTextureType type,
                           SDL_GPUTextureFormat format,
                           SDL_GPUTextureUsageFlags usage, uint32_t width,
                           uint32_t height, uint32_t layerCountOrDepth,
                           uint32_t numLevels, SDL_GPUSampleCount sampleCount);

    std::unique_ptr<SDL_GPUTexture, SDL_GPUTextureDeleter> ptr_{nullptr};
};

} // namespace ejff::gpu
