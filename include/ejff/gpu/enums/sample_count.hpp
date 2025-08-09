#pragma once

#include <SDL3/SDL.h>

namespace ejff::gpu
{

enum class SampleCount 
{
    e1 = SDL_GPU_SAMPLECOUNT_1,
    e2 = SDL_GPU_SAMPLECOUNT_2,
    e4 = SDL_GPU_SAMPLECOUNT_4,
    e8 = SDL_GPU_SAMPLECOUNT_8
};

} // namespace ejff::gpu
