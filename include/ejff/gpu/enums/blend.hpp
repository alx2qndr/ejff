#pragma once

#include "ejff/utilities/enable_bit_mask_operators.hpp"

#include <SDL3/SDL.h>

namespace ejff::gpu
{

enum class BlendFactor : uint64_t
{
    eInvalid = SDL_GPU_BLENDFACTOR_INVALID,
    eZero = SDL_GPU_BLENDFACTOR_ZERO,
    eOne = SDL_GPU_BLENDFACTOR_ONE,
    eSrcColor = SDL_GPU_BLENDFACTOR_SRC_COLOR,
    eOneMinusSrcColor = SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_COLOR,
    eDstColor = SDL_GPU_BLENDFACTOR_DST_COLOR,
    eOneMinusDstColor = SDL_GPU_BLENDFACTOR_ONE_MINUS_DST_COLOR,
    eSrcAlpha = SDL_GPU_BLENDFACTOR_SRC_ALPHA,
    eOneMinusSrcAlpha = SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
    eDstAlpha = SDL_GPU_BLENDFACTOR_DST_ALPHA,
    eOneMinusDstAlpha = SDL_GPU_BLENDFACTOR_ONE_MINUS_DST_ALPHA,
    eConstantColor = SDL_GPU_BLENDFACTOR_CONSTANT_COLOR,
    eOneMinusConstantColor = SDL_GPU_BLENDFACTOR_ONE_MINUS_CONSTANT_COLOR,
    eSrcAlphaSaturate = SDL_GPU_BLENDFACTOR_SRC_ALPHA_SATURATE
};

enum class BlendOp : uint64_t
{
    eInvalid = SDL_GPU_BLENDOP_INVALID,
    eAdd = SDL_GPU_BLENDOP_ADD,
    eSubtract = SDL_GPU_BLENDOP_SUBTRACT,
    eReverseSubtract = SDL_GPU_BLENDOP_REVERSE_SUBTRACT,
    eMin = SDL_GPU_BLENDOP_MIN,
    eMax = SDL_GPU_BLENDOP_MAX
};

enum class ColorComponentFlags : uint64_t
{
    eR = SDL_GPU_COLORCOMPONENT_R,
    eG = SDL_GPU_COLORCOMPONENT_G,
    eB = SDL_GPU_COLORCOMPONENT_B,
    eA = SDL_GPU_COLORCOMPONENT_A
};

} // namespace ejff::gpu

ENABLE_BITMASK_OPERATORS(ejff::gpu::ColorComponentFlags);