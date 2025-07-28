#pragma once

#include <memory>

#include <SDL3/SDL.h>

namespace ejff::gpu
{

class Device;

struct SDL_GPUCommandBufferDeleter
{
    void operator()(SDL_GPUCommandBuffer *commandBuffer) const noexcept
    {
        if (commandBuffer)
        {
            SDL_SubmitGPUCommandBuffer(commandBuffer);
        }
    }
};
class CommandBuffer
{
public:
    CommandBuffer() = default;

    explicit CommandBuffer(Device &device);

    CommandBuffer(const CommandBuffer &) = delete;
    CommandBuffer &operator=(const CommandBuffer &) = delete;

    CommandBuffer(CommandBuffer &&) noexcept = default;
    CommandBuffer &operator=(CommandBuffer &&) noexcept = default;

    ~CommandBuffer() = default;

    void submit();

    SDL_GPUCommandBuffer *get() const noexcept { return ptr_.get(); }

private:
    SDL_GPUCommandBuffer *acquire(Device &device);

    std::unique_ptr<SDL_GPUCommandBuffer, SDL_GPUCommandBufferDeleter> ptr_{nullptr};
};

} // namespace ejff::gpu