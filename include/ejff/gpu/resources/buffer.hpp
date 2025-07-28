#pragma once

#include "ejff/utilities/enable_bit_mask_operators.hpp"

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
    enum class UsageFlags : uint64_t
    {
        eVertex = SDL_GPU_BUFFERUSAGE_VERTEX,
        eIndex = SDL_GPU_BUFFERUSAGE_INDEX,
        eIndirect = SDL_GPU_BUFFERUSAGE_INDIRECT,
        eGraphicsStorageRead = SDL_GPU_BUFFERUSAGE_GRAPHICS_STORAGE_READ,
        eComputeStorageRead = SDL_GPU_BUFFERUSAGE_COMPUTE_STORAGE_READ,
        eComputeStorageWrite = SDL_GPU_BUFFERUSAGE_COMPUTE_STORAGE_WRITE
    };

    Buffer() = default;
    explicit Buffer(Device &device, UsageFlags usage, uint32_t size);

    Buffer(const Buffer &) = delete;
    Buffer &operator=(const Buffer &) = delete;

    Buffer(Buffer &&) noexcept = default;
    Buffer &operator=(Buffer &&) noexcept = default;

    ~Buffer() = default;

    SDL_GPUBuffer *get() const noexcept { return ptr_.get(); }

private:
    SDL_GPUBuffer *create(Device &device, UsageFlags usage, uint32_t size);

    std::unique_ptr<SDL_GPUBuffer, SDL_GPUBufferDeleter> ptr_{nullptr};
};

} // namespace ejff::gpu

ENABLE_BITMASK_OPERATORS(ejff::gpu::Buffer::UsageFlags)