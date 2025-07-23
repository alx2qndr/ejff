#pragma once

#include "ejff/gpu/device.hpp"

#include <memory>

#include <SDL3/SDL.h>

namespace ejff::gpu::resources
{

struct SDL_GPUBufferDeleter
{
    SDL_GPUDevice *device;

    SDL_GPUBufferDeleter(SDL_GPUDevice *device = nullptr) : device(device) {}

    void operator()(SDL_GPUBuffer *buffer) const noexcept
    {
        if (buffer)
        {
            SDL_ReleaseGPUBuffer(device, buffer);
        }
    }
};

class Buffer
{
public:
    Buffer() = default;

    explicit Buffer(Device &device, SDL_GPUBufferUsageFlags usage, Uint32 size);

    Buffer(const Buffer &) = delete;
    Buffer &operator=(const Buffer &) = delete;

    Buffer(Buffer &&) noexcept = default;
    Buffer &operator=(Buffer &&) noexcept = default;

    ~Buffer() = default;

    void reset(SDL_GPUBuffer *new_buffer = nullptr) noexcept { ptr_.reset(new_buffer); }

    SDL_GPUBuffer *release() noexcept { return ptr_.release(); }

    SDL_GPUBuffer *get() noexcept { return ptr_.get(); }
    
    SDL_GPUBuffer *get() const noexcept { return ptr_.get(); }

    explicit operator bool() const noexcept { return ptr_ != nullptr; }

private:
    std::unique_ptr<SDL_GPUBuffer, SDL_GPUBufferDeleter> ptr_;
};

} // namespace ejff::gpu::resources
