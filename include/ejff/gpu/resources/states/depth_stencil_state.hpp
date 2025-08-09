#pragma once

#include "ejff/gpu/enums/compare_op.hpp"
#include "ejff/gpu/resources/states/stencil_op_state.hpp"

#include <SDL3/SDL.h>

namespace ejff::gpu
{

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
