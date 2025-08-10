#pragma once

#include <SDL3/SDL.h>

namespace ejff::gpu
{

enum class SamplerMipmapMode
{
    eNearest = SDL_GPU_SAMPLERMIPMAPMODE_NEAREST,
    eLinear = SDL_GPU_SAMPLERMIPMAPMODE_LINEAR
};

} // namespace ejff::gpu