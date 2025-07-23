#include "ejff/gpu/resources/copy_pass.hpp"

#include <stdexcept>

#include <fmt/format.h>

namespace ejff::gpu::resources
{

CopyPass::CopyPass(CommandBuffer &command_buffer) : ptr_(nullptr, SDL_GPUCopyPassDeleter{})
{
    auto copy_pass = SDL_BeginGPUCopyPass(command_buffer.get());
    if (!copy_pass)
    {
        throw std::runtime_error(fmt::format(
            "Couldn't create SDL_GPUCopyPass. SDL_BeginGPUCopyPass failed: {}", SDL_GetError()));
    }

    ptr_.reset(copy_pass);
}

} // namespace ejff::gpu::resources