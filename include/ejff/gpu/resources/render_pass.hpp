#pragma once

#include "ejff/gpu/resources/command_buffer.hpp"

#include <memory>

#include <SDL3/SDL.h>

namespace ejff::gpu::resources
{

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

    explicit RenderPass(CommandBuffer &command_buffer,
                        const SDL_GPUColorTargetInfo *color_target_infos, Uint32 num_color_targets,
                        const SDL_GPUDepthStencilTargetInfo *depth_stencil_target_info);

    RenderPass(const RenderPass &) = delete;
    RenderPass &operator=(const RenderPass &) = delete;

    RenderPass(RenderPass &&) noexcept = default;
    RenderPass &operator=(RenderPass &&) noexcept = default;

    ~RenderPass() = default;

    void reset(SDL_GPURenderPass *new_render_pass = nullptr) noexcept
    {
        ptr_.reset(new_render_pass);
    }

    SDL_GPURenderPass *release() noexcept { return ptr_.release(); }

    explicit operator bool() const noexcept { return ptr_ != nullptr; }

    SDL_GPURenderPass *get() noexcept { return ptr_.get(); }
    SDL_GPURenderPass *get() const noexcept { return ptr_.get(); }

private:
    std::unique_ptr<SDL_GPURenderPass, SDL_GPURenderPassDeleter> ptr_;
};

} // namespace ejff::gpu::resources
