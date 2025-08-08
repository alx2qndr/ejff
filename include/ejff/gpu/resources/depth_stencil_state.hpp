#pragma once

#include "ejff/gpu/enums/depth_stencil.hpp"
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

struct DepthStencilState
{
    CompareOp compareOp{};
    StencilOpState backStencilState{};
    StencilOpState frontStencilState{};
    uint8_t compareMask = 0;
    uint8_t writeMask = 0;
    bool enableDepthTest = false;
    bool enableDepthWrite = false;
    bool enableStencilTest = false;

    SDL_GPUDepthStencilState get() const
    {
        SDL_GPUDepthStencilState state{};
        state.compare_op = static_cast<SDL_GPUCompareOp>(compareOp);
        state.back_stencil_state = backStencilState.get();
        state.front_stencil_state = frontStencilState.get();
        return state;
    }
};

} // namespace ejff::gpu
