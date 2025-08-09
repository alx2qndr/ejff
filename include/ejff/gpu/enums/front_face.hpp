#pragma once

#include <SDL3/SDL.h>

namespace ejff::gpu
{

enum class FrontFace 
{
    eCounterClockWise = SDL_GPU_FRONTFACE_COUNTER_CLOCKWISE,
    eClockWise = SDL_GPU_FRONTFACE_CLOCKWISE
};

} // namespace ejff::gpu
