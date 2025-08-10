#pragma once

#include "ejff/gpu/resources/color_target_description.hpp"

#include <vector>

namespace ejff::gpu
{

struct GraphicsPipelineTargetInfo
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
            static std::vector<SDL_GPUColorTargetDescription> colorDescs;
            colorDescs.clear();
            for (uint32_t i = 0; i < colorTargetCount; ++i)
            {
                colorDescs.push_back(pColorTargetDescriptions[i].get());
            }
            targetInfo.color_target_descriptions = colorDescs.data();
        }
        targetInfo.num_color_targets = colorTargetCount;
        targetInfo.depth_stencil_format =
            static_cast<SDL_GPUTextureFormat>(depthStencilFormat);
        targetInfo.has_depth_stencil_target = hasDepthStencilTarget;
        return targetInfo;
    }
};

} // namespace ejff::gpu