#pragma once

#include <SDL3/SDL.h>

namespace ejff::gpu
{

enum class FillMode : uint64_t
{
    eFill = SDL_GPU_FILLMODE_FILL,
    eLine = SDL_GPU_FILLMODE_LINE
};

enum class CullMode : uint64_t
{
    eNone = SDL_GPU_CULLMODE_NONE,
    eFront = SDL_GPU_CULLMODE_FRONT,
    eBack = SDL_GPU_CULLMODE_BACK
};

enum class FrontFace : uint64_t
{
    eCounterClockWise = SDL_GPU_FRONTFACE_COUNTER_CLOCKWISE,
    eClockWise = SDL_GPU_FRONTFACE_CLOCKWISE
};

} // namespace ejff::gpu
