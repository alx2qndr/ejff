#include "ejff/gpu/resources/render_pass.hpp"
#include "ejff/gpu/resources/command_buffer.hpp"

#include <stdexcept>

#include <fmt/format.h>

namespace ejff::gpu
{

RenderPass::RenderPass(CommandBuffer &commandBuffer,
                       const SDL_GPUColorTargetInfo *colorTargetInfos,
                       uint32_t numColorTargets,
                       const SDL_GPUDepthStencilTargetInfo *depthStencilTargetInfo)
    : ptr_(create(commandBuffer, colorTargetInfos, numColorTargets,
                  depthStencilTargetInfo),
           SDL_GPURenderPassDeleter{})
{
}

SDL_GPURenderPass *RenderPass::create(
    CommandBuffer &commandBuffer, const SDL_GPUColorTargetInfo *colorTargetInfos,
    uint32_t numColorTargets, const SDL_GPUDepthStencilTargetInfo *depthStencilTargetInfo)
{
    auto renderPass = SDL_BeginGPURenderPass(commandBuffer.get(), colorTargetInfos,
                                             numColorTargets, depthStencilTargetInfo);
    if (!renderPass)
    {
        throw std::runtime_error(fmt::format(
            "Couldn't begin SDL_GPURenderPass. SDL_BeginGPURenderPass failed: {}",
            SDL_GetError()));
    }

    return renderPass;
}

} // namespace ejff::gpu