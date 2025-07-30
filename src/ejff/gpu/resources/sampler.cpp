#include "ejff/gpu/resources/sampler.hpp"
#include "ejff/gpu/device.hpp"

#include <stdexcept>

#include <fmt/format.h>

namespace ejff::gpu
{

Sampler::Sampler(Device &device, SDL_GPUFilter minFilter,
                 SDL_GPUFilter magFilter, SDL_GPUSamplerMipmapMode mipmapMode,
                 SDL_GPUSamplerAddressMode addressModeU,
                 SDL_GPUSamplerAddressMode addressModeV,
                 SDL_GPUSamplerAddressMode addressModeW, float mipLodBias,
                 float maxAnisotropy, SDL_GPUCompareOp compareOp, float minLod,
                 float maxLod, bool enableAnisotropy, bool enableCompare)
    : ptr_(create(device, minFilter, magFilter, mipmapMode, addressModeU,
                  addressModeV, addressModeW, mipLodBias, maxAnisotropy,
                  compareOp, minLod, maxLod, enableAnisotropy, enableCompare),
           SDL_GPUSamplerDeleter{device.get()})
{
}

SDL_GPUSampler *Sampler::create(
    Device &device, SDL_GPUFilter minFilter, SDL_GPUFilter magFilter,
    SDL_GPUSamplerMipmapMode mipmapMode, SDL_GPUSamplerAddressMode addressModeU,
    SDL_GPUSamplerAddressMode addressModeV,
    SDL_GPUSamplerAddressMode addressModeW, float mipLodBias,
    float maxAnisotropy, SDL_GPUCompareOp compareOp, float minLod, float maxLod,
    bool enableAnisotropy, bool enableCompare)
{
    SDL_GPUSamplerCreateInfo createInfo{};
    createInfo.min_filter = minFilter;
    createInfo.mag_filter = magFilter;
    createInfo.mipmap_mode = mipmapMode;
    createInfo.address_mode_u = addressModeU;
    createInfo.address_mode_v = addressModeV;
    createInfo.address_mode_w = addressModeW;
    createInfo.mip_lod_bias = mipLodBias;
    createInfo.max_anisotropy = maxAnisotropy;
    createInfo.compare_op = compareOp;
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