#pragma once

#include <SDL3/SDL.h>

namespace ejff
{

enum class FlipMode
{
    eNone = SDL_FLIP_NONE,
    eHorizontal = SDL_FLIP_HORIZONTAL,
    eVertical = SDL_FLIP_VERTICAL
};

} // namespace ejff