#pragma once

#include <SDL3/SDL.h>

namespace ejff::gpu
{

enum class SamplerAddressMode
{
    eRepeat = SDL_GPU_SAMPLERADDRESSMODE_REPEAT,
    eMirroredRepeat = SDL_GPU_SAMPLERADDRESSMODE_MIRRORED_REPEAT,
    eClampToEdge = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE
};

} // namespace ejff::gpu