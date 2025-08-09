#pragma once

#include "ejff/gpu/enums/blend_factor.hpp"
#include "ejff/gpu/enums/blend_op.hpp"
#include "ejff/gpu/enums/color_component_flags.hpp"

#include <SDL3/SDL.h>

namespace ejff::gpu
{

struct ColorTargetBlendState
{
    BlendFactor srcColorBlendFactor{};
    BlendFactor dstColorBlendFactor{};
    BlendOp colorBlendOp{};
    BlendFactor srcAlphaBlendFactor{};
    BlendFactor dstAlphaBlendFactor{};
    BlendOp alphaBlendOp{};
    ColorComponentFlags colorWriteMask{};
    bool enableBlend = false;
    bool enableColorWriteMask = false;

    SDL_GPUColorTargetBlendState get() const
    {
        SDL_GPUColorTargetBlendState state{};
        state.src_color_blendfactor =
            static_cast<SDL_GPUBlendFactor>(srcColorBlendFactor);
        state.dst_color_blendfactor =
            static_cast<SDL_GPUBlendFactor>(dstColorBlendFactor);
        state.color_blend_op = static_cast<SDL_GPUBlendOp>(colorBlendOp);
        state.src_alpha_blendfactor =
            static_cast<SDL_GPUBlendFactor>(srcAlphaBlendFactor);
        state.dst_alpha_blendfactor =
            static_cast<SDL_GPUBlendFactor>(dstAlphaBlendFactor);
        state.alpha_blend_op = static_cast<SDL_GPUBlendOp>(alphaBlendOp);
        state.enable_blend = enableBlend;
        state.color_write_mask =
            static_cast<SDL_GPUColorComponentFlags>(colorWriteMask);
        state.enable_color_write_mask = enableColorWriteMask;
        return state;
    }
};

} // namespace ejff::gpu
