#pragma once

#include <SDL3/SDL.h>

namespace ejff::gpu
{

enum class CompareOp : uint64_t
{
    eInvalid = SDL_GPU_COMPAREOP_INVALID,
    eNever = SDL_GPU_COMPAREOP_NEVER,
    eLess = SDL_GPU_COMPAREOP_LESS,
    eEqual = SDL_GPU_COMPAREOP_EQUAL,
    eLessOrEqual = SDL_GPU_COMPAREOP_LESS_OR_EQUAL,
    eGreater = SDL_GPU_COMPAREOP_GREATER,
    eNotEqual = SDL_GPU_COMPAREOP_NOT_EQUAL,
    eGreaterOrEqual = SDL_GPU_COMPAREOP_GREATER_OR_EQUAL,
    eAlways = SDL_GPU_COMPAREOP_ALWAYS
};

enum class StencilOp : uint64_t
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
