#pragma once

#include "ejff/gpu/enums/compare_op.hpp"
#include "ejff/gpu/enums/filter.hpp"
#include "ejff/gpu/enums/sampler_address_mode.hpp"
#include "ejff/gpu/enums/sampler_mipmap_mode.hpp"

#include <memory>

#include <SDL3/SDL.h>

namespace ejff::gpu
{

class Device;

struct SDL_GPUSamplerDeleter
{
    SDL_GPUDevice *device;

    SDL_GPUSamplerDeleter(SDL_GPUDevice *device = nullptr) : device(device) {}

    void operator()(SDL_GPUSampler *sampler) const noexcept
    {
        if (sampler)
        {
            SDL_ReleaseGPUSampler(device, sampler);
        }
    }
};

class Sampler
{
public:
    Sampler() = default;

    explicit Sampler(Device &device, Filter minFilter, Filter magFilter,
                     SamplerMipmapMode mipmapMode,
                     SamplerAddressMode addressModeU,
                     SamplerAddressMode addressModeV,
                     SamplerAddressMode addressModeW, float mipLodBias,
                     float maxAnisotropy, CompareOp compareOp, float minLod,
                     float maxLod, bool enableAnisotropy, bool enableCompare);

    Sampler(const Sampler &) = delete;
    Sampler &operator=(const Sampler &) = delete;

    Sampler(Sampler &&) noexcept = default;
    Sampler &operator=(Sampler &&) noexcept = default;

    ~Sampler() = default;

    SDL_GPUSampler *get() const noexcept { return ptr_.get(); }

private:
    SDL_GPUSampler *create(Device &device, Filter minFilter, Filter magFilter,
                           SamplerMipmapMode mipmapMode,
                           SamplerAddressMode addressModeU,
                           SamplerAddressMode addressModeV,
                           SamplerAddressMode addressModeW, float mipLodBias,
                           float maxAnisotropy, CompareOp compareOp,
                           float minLod, float maxLod, bool enableAnisotropy,
                           bool enableCompare);

    std::unique_ptr<SDL_GPUSampler, SDL_GPUSamplerDeleter> ptr_{nullptr};
};

} // namespace ejff::gpu
