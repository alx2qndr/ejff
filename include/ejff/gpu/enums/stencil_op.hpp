#pragma once

#include <SDL3/SDL.h>

namespace ejff::gpu
{

enum class StencilOp
{
    eInvalid = SDL_GPU_STENCILOP_INVALID,
    eKeep = SDL_GPU_STENCILOP_KEEP,
    eZero = SDL_GPU_STENCILOP_ZERO,
    eReplace = SDL_GPU_STENCILOP_REPLACE,
    eIncrementAndClamp = SDL_GPU_STENCILOP_INCREMENT_AND_CLAMP,
    eDecrementAndClamp = SDL_GPU_STENCILOP_DECREMENT_AND_CLAMP,
    eInvert = SDL_GPU_STENCILOP_INVERT,
    eIncrementAndWrap = SDL_GPU_STENCILOP_INCREMENT_AND_WRAP,
    eDecrementAndWrap = SDL_GPU_STENCILOP_DECREMENT_AND_WRAP
};

} // namespace ejff::gpu
