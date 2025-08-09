#pragma once

#include "ejff/utilities/enable_bit_mask_operators.hpp"

#include <SDL3/SDL.h>

namespace ejff::gpu
{

enum class TextureUsageFlags : uint32_t
{
    eSampler = SDL_GPU_TEXTUREUSAGE_SAMPLER,
    eColorTarget = SDL_GPU_TEXTUREUSAGE_COLOR_TARGET,
    eDepthStencilTarget = SDL_GPU_TEXTUREUSAGE_DEPTH_STENCIL_TARGET,
    eGraphicsStorageRead = SDL_GPU_TEXTUREUSAGE_GRAPHICS_STORAGE_READ,
    eComputeStorageRead = SDL_GPU_TEXTUREUSAGE_COMPUTE_STORAGE_READ,
    eComputeStorageWrite = SDL_GPU_TEXTUREUSAGE_COMPUTE_STORAGE_WRITE,
    eComputeStorageSimultaneousReadWrite =
        SDL_GPU_TEXTUREUSAGE_COMPUTE_STORAGE_SIMULTANEOUS_READ_WRITE
};

} // namespace ejff::gpu

ENABLE_BITMASK_OPERATORS(ejff::gpu::TextureUsageFlags);