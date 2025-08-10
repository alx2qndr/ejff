#pragma once

#include <SDL3/SDL.h>

namespace ejff::gpu
{

enum class LoadOp
{
    eLoad = SDL_GPU_LOADOP_LOAD,
    eClear = SDL_GPU_LOADOP_CLEAR,
    eDontCare = SDL_GPU_LOADOP_DONT_CARE
};

} // namespace ejff::gpu