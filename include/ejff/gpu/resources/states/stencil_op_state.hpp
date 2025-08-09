#pragma once

#include "ejff/gpu/enums/compare_op.hpp"
#include "ejff/gpu/enums/stencil_op.hpp"

#include <SDL3/SDL.h>

namespace ejff::gpu
{

struct StencilOpState
{
    StencilOp failOp{};
    StencilOp passOp{};
    StencilOp depthFailOp{};
    CompareOp compareOp{};

    SDL_GPUStencilOpState get() const
    {
        SDL_GPUStencilOpState state{};
        state.fail_op = static_cast<SDL_GPUStencilOp>(failOp);
        state.pass_op = static_cast<SDL_GPUStencilOp>(passOp);
        state.depth_fail_op = static_cast<SDL_GPUStencilOp>(depthFailOp);
        state.compare_op = static_cast<SDL_GPUCompareOp>(compareOp);
        return state;
    }
};

} // namespace ejff::gpu