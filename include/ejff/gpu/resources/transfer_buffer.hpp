#pragma once

#include "ejff/gpu/device.hpp"

#include <memory>

#include <SDL3/SDL.h>

namespace ejff::gpu
{

struct SDL_GPUTransferBufferDeleter
{
    SDL_GPUDevice *device;

    SDL_GPUTransferBufferDeleter(SDL_GPUDevice *device = nullptr) : device(device) {}

    void operator()(SDL_GPUTransferBuffer *transfer_buffer) const noexcept
    {
        if (transfer_buffer)
        {
            SDL_ReleaseGPUTransferBuffer(device, transfer_buffer);
        }
    }
};

class TransferBuffer
{
public:
    TransferBuffer() = default;

    explicit TransferBuffer(Device &device, SDL_GPUTransferBufferUsage usage, Uint32 size);

    TransferBuffer(const TransferBuffer &) = delete;
    TransferBuffer &operator=(const TransferBuffer &) = delete;

    TransferBuffer(TransferBuffer &&) noexcept = default;
    TransferBuffer &operator=(TransferBuffer &&) noexcept = default;

    ~TransferBuffer() = default;

    void upload(Device &device, const void *data, std::size_t size, std::size_t offset = 0);
    
    void reset(SDL_GPUTransferBuffer *new_transfer_buffer = nullptr) noexcept
    {
        ptr_.reset(new_transfer_buffer);
    }

    SDL_GPUTransferBuffer *release() noexcept { return ptr_.release(); }

    SDL_GPUTransferBuffer *get() noexcept { return ptr_.get(); }
    
    SDL_GPUTransferBuffer *get() const noexcept { return ptr_.get(); }

    explicit operator bool() const noexcept { return ptr_ != nullptr; }

private:
    std::unique_ptr<SDL_GPUTransferBuffer, SDL_GPUTransferBufferDeleter> ptr_;
};

} // namespace ejff::gpu
