#pragma once

#include "ejff/gpu/enums/rasterizer.hpp"

#include <SDL3/SDL.h>

namespace ejff::gpu
{

struct RasterizerState
{
    FillMode fillMode{};
    CullMode cullMode{};
    FrontFace frontFace{};
    float depthBiasConstantFactor = 0.0f;
    float depthBiasClamp = 0.0f;
    float depthBiasSlopeFactor = 0.0f;
    bool enableDepthBias = false;
    bool enableDepthClip = false;

    SDL_GPURasterizerState get() const
    {
        SDL_GPURasterizerState state{};
        state.fill_mode = static_cast<SDL_GPUFillMode>(fillMode);
        state.cull_mode = static_cast<SDL_GPUCullMode>(cullMode);
        state.front_face = static_cast<SDL_GPUFrontFace>(frontFace);
        state.depth_bias_constant_factor = depthBiasConstantFactor;
        state.depth_bias_clamp = depthBiasClamp;
        state.depth_bias_slope_factor = depthBiasSlopeFactor;
        state.enable_depth_bias = enableDepthBias;
        state.enable_depth_clip = enableDepthClip;
        return state;
    }
};

} // namespace ejff::gpu
