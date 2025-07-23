#include "ejff/gpu/resources/render_pass.hpp"

#include <stdexcept>

#include <fmt/format.h>

namespace ejff::gpu::resources
{

RenderPass::RenderPass(CommandBuffer &command_buffer,
                       const SDL_GPUColorTargetInfo *color_target_infos, Uint32 num_color_targets,
                       const SDL_GPUDepthStencilTargetInfo *depth_stencil_target_info)
    : ptr_(nullptr, SDL_GPURenderPassDeleter{})
{
    auto render_pass = SDL_BeginGPURenderPass(command_buffer.get(), color_target_infos,
                                              num_color_targets, depth_stencil_target_info);
    if (!render_pass)
    {
        throw std::runtime_error(fmt::format(
            "Couldn't begin SDL_GPURenderPass. SDL_BeginGPURenderPass failed: {}", SDL_GetError()));
    }

    ptr_.reset(render_pass);
}

} // namespace ejff::gpu::resources