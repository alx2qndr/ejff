#pragma once

#include <SDL3/SDL.h>

namespace ejff::gpu
{

enum class PrimitiveType
{
    eTriangleList = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST,
    eTriangleStrip = SDL_GPU_PRIMITIVETYPE_TRIANGLESTRIP,
    eLineList = SDL_GPU_PRIMITIVETYPE_LINELIST,
    eLineStrip = SDL_GPU_PRIMITIVETYPE_LINESTRIP,
    ePointList = SDL_GPU_PRIMITIVETYPE_POINTLIST
};

} // namespace ejff::gpu
