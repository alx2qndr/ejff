#include "ejff/gpu/resources/sampler.hpp"

#include <stdexcept>

#include <fmt/format.h>

namespace ejff::gpu
{

Sampler::Sampler(Device &device, SDL_GPUFilter min_filter, SDL_GPUFilter mag_filter,
                 SDL_GPUSamplerMipmapMode mipmap_mode, SDL_GPUSamplerAddressMode address_mode_u,
                 SDL_GPUSamplerAddressMode address_mode_v, SDL_GPUSamplerAddressMode address_mode_w,
                 float mip_lod_bias, float max_anisotropy, SDL_GPUCompareOp compare_op,
                 float min_lod, float max_lod, bool enable_anisotropy, bool enable_compare)
    : ptr_(nullptr, SDL_GPUSamplerDeleter{device.get()})
{
    SDL_GPUSamplerCreateInfo createinfo{};
    createinfo.min_filter = min_filter;
    createinfo.mag_filter = mag_filter;
    createinfo.mipmap_mode = mipmap_mode;
    createinfo.address_mode_u = address_mode_u;
    createinfo.address_mode_v = address_mode_v;
    createinfo.address_mode_w = address_mode_w;
    createinfo.mip_lod_bias = mip_lod_bias;
    createinfo.max_anisotropy = max_anisotropy;
    createinfo.compare_op = compare_op;
    createinfo.min_lod = min_lod;
    createinfo.max_lod = max_lod;
    createinfo.enable_anisotropy = enable_anisotropy;
    createinfo.enable_compare = enable_compare;

    auto sampler = SDL_CreateGPUSampler(device.get(), &createinfo);
    if (!sampler)
    {
        throw std::runtime_error(fmt::format("Couldn't create SDL_GPUSampler. "
                                             "SDL_CreateGPUSampler failed: {}",
                                             SDL_GetError()));
    }

    ptr_.reset(sampler);
}

} // namespace ejff::gpu