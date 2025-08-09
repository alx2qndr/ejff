#pragma once

#include <SDL3/SDL.h>

namespace ejff::gpu
{

enum class CompareOp 
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

} // namespace ejff::gpu
