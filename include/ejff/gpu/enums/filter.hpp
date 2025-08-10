#pragma once

#include <SDL3/SDL.h>

namespace ejff::gpu
{

enum class Filter
{
    eNearest = SDL_GPU_FILTER_NEAREST,
    eLinear = SDL_GPU_FILTER_LINEAR
};

} // namespace ejff::gpu