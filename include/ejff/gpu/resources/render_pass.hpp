#pragma once

#include <memory>

#include <SDL3/SDL.h>

namespace ejff::gpu
{

class CommandBuffer;

struct SDL_GPURenderPassDeleter
{
    void operator()(SDL_GPURenderPass *render_pass) const noexcept
    {
        if (render_pass)
        {
            SDL_EndGPURenderPass(render_pass);
        }
    }
};

class RenderPass
{
public:
    RenderPass() = default;

    explicit RenderPass(CommandBuffer &commandBuffer,
                        const SDL_GPUColorTargetInfo *colorTargetInfos,
                        uint32_t numColorTargets,
                        const SDL_GPUDepthStencilTargetInfo *depthStencilTargetInfo);

    RenderPass(const RenderPass &) = delete;
    RenderPass &operator=(const RenderPass &) = delete;

    RenderPass(RenderPass &&) noexcept = default;
    RenderPass &operator=(RenderPass &&) noexcept = default;

    ~RenderPass() = default;

    SDL_GPURenderPass *get() const noexcept { return ptr_.get(); }

private:
    SDL_GPURenderPass *create(
        CommandBuffer &commandBuffer, const SDL_GPUColorTargetInfo *colorTargetInfos,
        uint32_t numColorTargets,
        const SDL_GPUDepthStencilTargetInfo *depthStencilTargetInfo);

    std::unique_ptr<SDL_GPURenderPass, SDL_GPURenderPassDeleter> ptr_{nullptr};
};

} // namespace ejff::gpu
