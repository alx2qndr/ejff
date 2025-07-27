#pragma once

#include "ejff/gpu/device.hpp"

#include <memory>

#include <SDL3/SDL.h>

namespace ejff::gpu::resources
{

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

    explicit Texture(Device &device, SDL_GPUTextureType type, SDL_GPUTextureFormat format,
                     SDL_GPUTextureUsageFlags usage, Uint32 width, Uint32 height,
                     Uint32 layer_count_or_depth, Uint32 num_levels,
                     SDL_GPUSampleCount sample_count);

    Texture(const Texture &) = delete;
    Texture &operator=(const Texture &) = delete;

    Texture(Texture &&) noexcept = default;
    Texture &operator=(Texture &&) noexcept = default;

    ~Texture() = default;

    void reset(SDL_GPUTexture *new_texture = nullptr) noexcept { ptr_.reset(new_texture); }

    SDL_GPUTexture *release() noexcept { return ptr_.release(); }

    explicit operator bool() const noexcept { return ptr_ != nullptr; }

    SDL_GPUTexture *get() noexcept { return ptr_.get(); }
    SDL_GPUTexture *get() const noexcept { return ptr_.get(); }

private:
    std::unique_ptr<SDL_GPUTexture, SDL_GPUTextureDeleter> ptr_;
};

} // namespace ejff::gpu::resources
