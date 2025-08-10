#pragma once

#include "ejff/gpu/enums/texture_format.hpp"
#include "ejff/gpu/resources/states/color_target_blend_state.hpp"

#include <SDL3/SDL.h>

namespace ejff::gpu
{

struct ColorTargetBlendState;

struct ColorTargetDescription
{
    TextureFormat format = TextureFormat::eInvalid;
    ColorTargetBlendState blendState{};

    SDL_GPUColorTargetDescription get() const
    {
        SDL_GPUColorTargetDescription description{};
        description.format = static_cast<SDL_GPUTextureFormat>(format);
        description.blend_state = blendState.get();
        return description;
    }
};

} // namespace ejff::gpu
