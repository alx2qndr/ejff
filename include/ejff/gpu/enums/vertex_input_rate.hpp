#pragma once

#include <SDL3/SDL.h>

namespace ejff::gpu
{

enum class VertexInputRate
{
    eVertex = SDL_GPU_VERTEXINPUTRATE_VERTEX,
    eInstance = SDL_GPU_VERTEXINPUTRATE_INSTANCE
};

} // namespace ejff::gpu
