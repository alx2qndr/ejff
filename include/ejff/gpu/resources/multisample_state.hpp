#pragma once

#include "ejff/gpu/enums/sample.hpp"

#include <SDL3/SDL.h>

namespace ejff::gpu
{

struct MultisampleState
{
    SampleCount sampleCount = SampleCount::e1;
    uint32_t sampleMask = 0;
    bool enableMask = false;

    SDL_GPUMultisampleState get() const
    {
        SDL_GPUMultisampleState state{};
        state.sample_count = static_cast<SDL_GPUSampleCount>(sampleCount);
        state.sample_mask = static_cast<Uint32>(sampleMask);
        state.enable_mask = enableMask;
        return state;
    }
};

} // namespace ejff::gpu
