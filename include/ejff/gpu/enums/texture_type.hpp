#pragma once

#include <SDL3/SDL.h>

namespace ejff::gpu
{

enum class TextureType
{
    e2D = SDL_GPU_TEXTURETYPE_2D,
    e2DArray = SDL_GPU_TEXTURETYPE_2D_ARRAY,
    e3D = SDL_GPU_TEXTURETYPE_3D,
    eCube = SDL_GPU_TEXTURETYPE_CUBE,
    eCubeArray = SDL_GPU_TEXTURETYPE_CUBE_ARRAY
};

} // namespace ejff::gpu