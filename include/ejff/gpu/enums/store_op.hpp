#pragma once

#include <SDL3/SDL.h>

namespace ejff::gpu
{

enum class StoreOp
{
    eStore = SDL_GPU_STOREOP_STORE,
    eDontCare = SDL_GPU_STOREOP_DONT_CARE,
    eResolve = SDL_GPU_STOREOP_RESOLVE,
    eResolveAndStore = SDL_GPU_STOREOP_RESOLVE_AND_STORE
};

} // namespace ejff::gpu