#pragma once

#include "ejff/gpu/device.hpp"

#include <memory>

#include <SDL3/SDL.h>

namespace ejff::gpu::resources
{

struct SDL_GPUCommandBufferDeleter
{
    void operator()(SDL_GPUCommandBuffer *command_buffer) const noexcept
    {
        if (command_buffer)
        {
            SDL_SubmitGPUCommandBuffer(command_buffer);
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

    void reset(SDL_GPUCommandBuffer *new_command_buffer = nullptr) noexcept
    {
        ptr_.reset(new_command_buffer);
    }

    SDL_GPUCommandBuffer *release() noexcept { return ptr_.release(); }

    SDL_GPUCommandBuffer *get() noexcept { return ptr_.get(); }

    SDL_GPUCommandBuffer *get() const noexcept { return ptr_.get(); }

    explicit operator bool() const noexcept { return ptr_ != nullptr; }

private:
    std::unique_ptr<SDL_GPUCommandBuffer, SDL_GPUCommandBufferDeleter> ptr_;
};

} // namespace ejff::gpu::resources
