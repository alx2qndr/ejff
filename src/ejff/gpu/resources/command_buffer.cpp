#include "ejff/gpu/resources/command_buffer.hpp"

#include <stdexcept>

#include <fmt/format.h>

namespace ejff::gpu
{

CommandBuffer::CommandBuffer(Device &device)
    : ptr_(nullptr, SDL_GPUCommandBufferDeleter{})
{
    auto command_buffer = SDL_AcquireGPUCommandBuffer(device.get());
    if (!command_buffer)
    {
        throw std::runtime_error(fmt::format("Couldn't create SDL_GPUCommandBuffer. "
                                             "SDL_AcquireGPUCommandBuffer failed: {}",
                                             SDL_GetError()));
    }

    ptr_.reset(command_buffer);
}

} // namespace ejff::gpu