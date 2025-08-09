#pragma once

#include <SDL3/SDL.h>

namespace ejff::gpu
{

enum class FillMode 
{
    eFill = SDL_GPU_FILLMODE_FILL,
    eLine = SDL_GPU_FILLMODE_LINE
};

} // namespace ejff::gpu
