#pragma once

#include "ejff/utilities/enable_bit_mask_operators.hpp"

#include <SDL3/SDL.h>

namespace ejff::gpu
{

enum class ColorComponentFlags : uint8_t
{
    eR = SDL_GPU_COLORCOMPONENT_R,
    eG = SDL_GPU_COLORCOMPONENT_G,
    eB = SDL_GPU_COLORCOMPONENT_B,
    eA = SDL_GPU_COLORCOMPONENT_A
};

} // namespace ejff

ENABLE_BITMASK_OPERATORS(ejff::gpu::ColorComponentFlags);