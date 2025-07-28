#include "ejff/gpu/resources/transfer_buffer.hpp"
#include "ejff/gpu/device.hpp"

#include <stdexcept>

#include <fmt/format.h>

namespace ejff::gpu
{

TransferBuffer::TransferBuffer(Device &device, SDL_GPUTransferBufferUsage usage,
                               Uint32 size)
    : ptr_(create(device, usage, size), SDL_GPUTransferBufferDeleter{device.get()})
{
}

void TransferBuffer::upload(Device &device, const void *data, std::size_t size,
                            std::size_t offset)
{
    void *mapped = SDL_MapGPUTransferBuffer(device.get(), ptr_.get(), false);
    if (!mapped)
    {
        throw std::runtime_error(fmt::format(
            "Couldn't map SDL_GPUTransferBuffer. SDL_MapGPUTransferBuffer failed: {}",
            SDL_GetError()));
    }

    std::memcpy(static_cast<std::uint8_t *>(mapped) + offset, data, size);

    SDL_UnmapGPUTransferBuffer(device.get(), ptr_.get());
}

SDL_GPUTransferBuffer *TransferBuffer::create(Device &device,
                                              SDL_GPUTransferBufferUsage usage,
                                              uint32_t size)
{
    SDL_GPUTransferBufferCreateInfo createInfo{};
    createInfo.usage = usage;
    createInfo.size = static_cast<Uint32>(size);

    auto transferBuffer = SDL_CreateGPUTransferBuffer(device.get(), &createInfo);
    if (!transferBuffer)
    {
        throw std::runtime_error(fmt::format("Couldn't create SDL_GPUTransferBuffer. "
                                             "SDL_CreateGPUTransferBuffer failed: {}",
                                             SDL_GetError()));
    }

    return transferBuffer;
}

} // namespace ejff::gpu