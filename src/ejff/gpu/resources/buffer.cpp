#include "ejff/gpu/resources/buffer.hpp"
#include "ejff/gpu/device.hpp"

#include <stdexcept>

#include <fmt/format.h>

namespace ejff::gpu
{

Buffer::Buffer(Device &device, UsageFlags usage, uint32_t size)
    : ptr_(create(device, usage, size), SDL_GPUBufferDeleter{device.get()})
{
}

SDL_GPUBuffer *Buffer::create(Device &device, UsageFlags usage, uint32_t size)
{
    SDL_GPUBufferCreateInfo createinfo{};
    createinfo.usage = static_cast<SDL_GPUBufferUsageFlags>(usage);
    createinfo.size = static_cast<Uint32>(size);

    auto buffer = SDL_CreateGPUBuffer(device.get(), &createinfo);
    if (!buffer)
    {
        throw std::runtime_error(
            fmt::format("Couldn't create SDL_GPUBuffer. SDL_CreateGPUBuffer failed: {}",
                        SDL_GetError()));
    }

    return buffer;
}

} // namespace ejff::gpu