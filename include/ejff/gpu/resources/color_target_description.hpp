#pragma once

#include "ejff/gpu/enums/texture_format.hpp"
#include "ejff/gpu/resources/states/color_target_blend_state.hpp"

#include <vector>

#include <SDL3/SDL.h>

namespace ejff::gpu
{

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

struct TargetInfo
{
    const ColorTargetDescription *pColorTargetDescriptions = nullptr;
    uint32_t colorTargetCount = 0;
    TextureFormat depthStencilFormat = TextureFormat::eInvalid;
    bool hasDepthStencilTarget = false;

    SDL_GPUGraphicsPipelineTargetInfo get() const
    {
        SDL_GPUGraphicsPipelineTargetInfo targetInfo{};
        if (pColorTargetDescriptions)
        {
            static std::vector<SDL_GPUColorTargetDescription>
                colorTargetDescriptions;
            colorTargetDescriptions.clear();
            for (uint32_t i = 0; i < colorTargetCount; ++i)
            {
                colorTargetDescriptions.push_back(
                    pColorTargetDescriptions[i].get());
            }
            targetInfo.color_target_descriptions =
                colorTargetDescriptions.data();
        }
        targetInfo.num_color_targets = colorTargetCount;
        targetInfo.depth_stencil_format =
            static_cast<SDL_GPUTextureFormat>(depthStencilFormat);
        targetInfo.has_depth_stencil_target = hasDepthStencilTarget;
        return targetInfo;
    }
};

} // namespace ejff::gpu
