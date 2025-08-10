#include "ejff/gpu/resources/sampler.hpp"
#include "ejff/gpu/device.hpp"

#include <stdexcept>

#include <fmt/format.h>

namespace ejff::gpu
{

Sampler::Sampler(Device &device, Filter minFilter, Filter magFilter,
                 SamplerMipmapMode mipmapMode, SamplerAddressMode addressModeU,
                 SamplerAddressMode addressModeV,
                 SamplerAddressMode addressModeW, float mipLodBias,
                 float maxAnisotropy, CompareOp compareOp, float minLod,
                 float maxLod, bool enableAnisotropy, bool enableCompare)
    : ptr_(create(device, minFilter, magFilter, mipmapMode, addressModeU,
                  addressModeV, addressModeW, mipLodBias, maxAnisotropy,
                  compareOp, minLod, maxLod, enableAnisotropy, enableCompare),
           SDL_GPUSamplerDeleter{device.get()})
{
}

SDL_GPUSampler *Sampler::create(Device &device, Filter minFilter,
                                Filter magFilter, SamplerMipmapMode mipmapMode,
                                SamplerAddressMode addressModeU,
                                SamplerAddressMode addressModeV,
                                SamplerAddressMode addressModeW,
                                float mipLodBias, float maxAnisotropy,
                                CompareOp compareOp, float minLod, float maxLod,
                                bool enableAnisotropy, bool enableCompare)
{
    SDL_GPUSamplerCreateInfo createInfo{};
    createInfo.min_filter = static_cast<SDL_GPUFilter>(minFilter);
    createInfo.mag_filter = static_cast<SDL_GPUFilter>(magFilter);
    createInfo.mipmap_mode = static_cast<SDL_GPUSamplerMipmapMode>(mipmapMode);
    createInfo.address_mode_u =
        static_cast<SDL_GPUSamplerAddressMode>(addressModeU);
    createInfo.address_mode_v =
        static_cast<SDL_GPUSamplerAddressMode>(addressModeV);
    createInfo.address_mode_w =
        static_cast<SDL_GPUSamplerAddressMode>(addressModeW);
    createInfo.mip_lod_bias = mipLodBias;
    createInfo.max_anisotropy = maxAnisotropy;
    createInfo.compare_op = static_cast<SDL_GPUCompareOp>(compareOp);
    createInfo.min_lod = minLod;
    createInfo.max_lod = maxLod;
    createInfo.enable_anisotropy = enableAnisotropy;
    createInfo.enable_compare = enableCompare;

    auto sampler = SDL_CreateGPUSampler(device.get(), &createInfo);
    if (!sampler)
    {
        throw std::runtime_error(fmt::format("Couldn't create SDL_GPUSampler. "
                                             "SDL_CreateGPUSampler failed: {}",
                                             SDL_GetError()));
    }

    return sampler;
}

} // namespace ejff::gpu