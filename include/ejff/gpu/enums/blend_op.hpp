#pragma once

#include <SDL3/SDL.h>

namespace ejff::gpu
{

enum class BlendOp
{
    eInvalid = SDL_GPU_BLENDOP_INVALID,
    eAdd = SDL_GPU_BLENDOP_ADD,
    eSubtract = SDL_GPU_BLENDOP_SUBTRACT,
    eReverseSubtract = SDL_GPU_BLENDOP_REVERSE_SUBTRACT,
    eMin = SDL_GPU_BLENDOP_MIN,
    eMax = SDL_GPU_BLENDOP_MAX
};

} // namespace ejff::gpu
