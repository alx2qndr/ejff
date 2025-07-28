#include "ejff/gpu/resources/transfer_buffer.hpp"

#include <stdexcept>

#include <fmt/format.h>

namespace ejff::gpu
{

TransferBuffer::TransferBuffer(Device &device, SDL_GPUTransferBufferUsage usage, Uint32 size)
    : ptr_(nullptr, SDL_GPUTransferBufferDeleter{device.get()})
{
    SDL_GPUTransferBufferCreateInfo createinfo{};
    createinfo.usage = usage;
    createinfo.size = size;

    auto buffer = SDL_CreateGPUTransferBuffer(device.get(), &createinfo);
    if (!buffer)
    {
        throw std::runtime_error(fmt::format("Couldn't create SDL_GPUTransferBuffer. "
                                             "SDL_CreateGPUTransferBuffer failed: {}",
                                             SDL_GetError()));
    }

    ptr_.reset(buffer);
}

void TransferBuffer::upload(Device &device, const void *data, std::size_t size, std::size_t offset)
{
    void *mapped = SDL_MapGPUTransferBuffer(device.get(), ptr_.get(), false);
    if (!mapped)
    {
        throw std::runtime_error(
            fmt::format("Couldn't map SDL_GPUTransferBuffer. SDL_MapGPUTransferBuffer failed: {}",
                        SDL_GetError()));
    }

    std::memcpy(static_cast<std::uint8_t *>(mapped) + offset, data, size);

    SDL_UnmapGPUTransferBuffer(device.get(), ptr_.get());
}

} // namespace ejff::gpu