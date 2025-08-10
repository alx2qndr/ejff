#pragma once

#include "ejff/gpu/enums/buffer_usage_flags.hpp"

#include <memory>

#include <SDL3/SDL.h>

namespace ejff::gpu
{

class Device;

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
    explicit Buffer(Device &device, BufferUsageFlags usage, uint32_t size);

    Buffer(const Buffer &) = delete;
    Buffer &operator=(const Buffer &) = delete;

    Buffer(Buffer &&) noexcept = default;
    Buffer &operator=(Buffer &&) noexcept = default;

    ~Buffer() = default;

    SDL_GPUBuffer *get() const noexcept { return ptr_.get(); }

private:
    SDL_GPUBuffer *create(Device &device, BufferUsageFlags usage,
                          uint32_t size);

    std::unique_ptr<SDL_GPUBuffer, SDL_GPUBufferDeleter> ptr_{nullptr};
};

} // namespace ejff::gpu
