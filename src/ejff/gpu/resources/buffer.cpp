#include "ejff/gpu/resources/buffer.hpp"

#include <stdexcept>

#include <fmt/format.h>

namespace ejff::gpu
{

Buffer::Buffer(Device &device, SDL_GPUBufferUsageFlags usage, Uint32 size)
    : ptr_(nullptr, SDL_GPUBufferDeleter{device.get()})
{
    SDL_GPUBufferCreateInfo createinfo{};
    createinfo.usage = usage;
    createinfo.size = size;

    auto buffer = SDL_CreateGPUBuffer(device.get(), &createinfo);
    if (!buffer)
    {
        throw std::runtime_error(fmt::format(
            "Couldn't create SDL_GPUBuffer. SDL_CreateGPUBuffer failed: {}", SDL_GetError()));
    }

    ptr_.reset(buffer);
}

} // namespace ejff::gpu