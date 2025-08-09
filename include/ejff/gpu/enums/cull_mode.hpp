#pragma once

#include <SDL3/SDL.h>

namespace ejff::gpu
{

enum class CullMode 
{
    eNone = SDL_GPU_CULLMODE_NONE,
    eFront = SDL_GPU_CULLMODE_FRONT,
    eBack = SDL_GPU_CULLMODE_BACK
};

} // namespace ejff::gpu
