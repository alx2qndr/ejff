#pragma once

#include "ejff/utilities/enable_bit_mask_operators.hpp"

#include <SDL3/SDL.h>

namespace ejff::gpu
{

enum class BufferUsageFlags : uint32_t
{
    eVertex = SDL_GPU_BUFFERUSAGE_VERTEX,
    eIndex = SDL_GPU_BUFFERUSAGE_INDEX,
    eIndirect = SDL_GPU_BUFFERUSAGE_INDIRECT,
    eGraphicsStorageRead = SDL_GPU_BUFFERUSAGE_GRAPHICS_STORAGE_READ,
    eComputeStorageRead = SDL_GPU_BUFFERUSAGE_COMPUTE_STORAGE_READ,
    eComputeStorageWrite = SDL_GPU_BUFFERUSAGE_COMPUTE_STORAGE_WRITE
};

} // namespace ejff::gpu

ENABLE_BITMASK_OPERATORS(ejff::gpu::BufferUsageFlags);