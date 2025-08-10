#pragma once

#include "ejff/color.hpp"
#include "ejff/gpu/enums/load_op.hpp"
#include "ejff/gpu/enums/store_op.hpp"
#include "ejff/gpu/resources/texture.hpp"

#include <SDL3/SDL.h>

namespace ejff::gpu
{

struct ColorTargetInfo
{
    Texture texture;
    uint32_t mip_level;
    uint32_t layer_or_depth_plane;
    Color<float> clear_color;
    LoadOp load_op;
    StoreOp store_op;
    Texture resolveTexture;
    uint32_t resolveMipLevel;
    uint32_t resolveLayer;
    bool cycle;
    bool cycleResolveTexture;

    SDL_GPUColorTargetInfo get() const
    {
        SDL_GPUColorTargetInfo colorTargetInfo{};
        colorTargetInfo.texture = texture.get();
        colorTargetInfo.mip_level = static_cast<Uint32>(mip_level);
        colorTargetInfo.layer_or_depth_plane =
            static_cast<Uint32>(layer_or_depth_plane);

        colorTargetInfo.clear_color.r = clear_color.red();
        colorTargetInfo.clear_color.g = clear_color.green();
        colorTargetInfo.clear_color.b = clear_color.blue();
        colorTargetInfo.clear_color.a = clear_color.alpha();

        colorTargetInfo.load_op = static_cast<SDL_GPULoadOp>(load_op);
        colorTargetInfo.store_op = static_cast<SDL_GPUStoreOp>(store_op);

        colorTargetInfo.resolve_texture = resolveTexture.get();
        colorTargetInfo.resolve_mip_level =
            static_cast<Uint32>(resolveMipLevel);
        colorTargetInfo.resolve_layer = static_cast<Uint32>(resolveLayer);

        colorTargetInfo.cycle = cycle;
        colorTargetInfo.cycle_resolve_texture = cycleResolveTexture;

        return colorTargetInfo;
    }
};

} // namespace ejff::gpu
