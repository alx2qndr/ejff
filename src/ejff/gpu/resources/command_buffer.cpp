#include "ejff/gpu/resources/command_buffer.hpp"
#include "ejff/gpu/device.hpp"

#include <stdexcept>

#include <fmt/format.h>

namespace ejff::gpu
{

CommandBuffer::CommandBuffer(Device &device)
    : ptr_(create(device), SDL_GPUCommandBufferDeleter{})
{
}

void CommandBuffer::submit()
{
    if (!SDL_SubmitGPUCommandBuffer(ptr_.get()))
    {
        throw std::runtime_error(fmt::format(
            "Couldn't submit GPU command buffer. SDL_SubmitGPUCommandBuffer failed: {}",
            SDL_GetError()));
    }
}

SDL_GPUCommandBuffer *CommandBuffer::create(Device &device)
{
    auto commandBuffer = SDL_AcquireGPUCommandBuffer(device.get());
    if (!commandBuffer)
    {
        throw std::runtime_error(fmt::format("Couldn't create SDL_GPUCommandBuffer. "
                                             "SDL_AcquireGPUCommandBuffer failed: {}",
                                             SDL_GetError()));
    }

    return commandBuffer;
}

} // namespace ejff::gpu