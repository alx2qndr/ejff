#pragma once

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

class Device;

class TransferBuffer
{
public:
    TransferBuffer() = default;

    explicit TransferBuffer(Device &device, SDL_GPUTransferBufferUsage usage,
                            uint32_t size);

    TransferBuffer(const TransferBuffer &) = delete;
    TransferBuffer &operator=(const TransferBuffer &) = delete;

    TransferBuffer(TransferBuffer &&) noexcept = default;
    TransferBuffer &operator=(TransferBuffer &&) noexcept = default;

    ~TransferBuffer() = default;

    void upload(Device &device, const void *data, std::size_t size,
                std::size_t offset = 0);

    SDL_GPUTransferBuffer *get() const noexcept { return ptr_.get(); }

private:
    SDL_GPUTransferBuffer *create(Device &device, SDL_GPUTransferBufferUsage usage,
                                  uint32_t size);

    std::unique_ptr<SDL_GPUTransferBuffer, SDL_GPUTransferBufferDeleter> ptr_{nullptr};
};

} // namespace ejff::gpu
