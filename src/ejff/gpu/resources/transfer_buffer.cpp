#include "ejff/gpu/resources/transfer_buffer.hpp"

#include <stdexcept>

#include <fmt/format.h>

namespace ejff::gpu::resources
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
        throw std::runtime_error(fmt::format(
            "Couldn't create SDL_GPUTransferBuffer. SDL_CreateGPUTransferBuffer failed: {}",
            SDL_GetError()));
    }

    ptr_.reset(buffer);
}

} // namespace ejff::gpu::resources