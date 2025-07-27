#pragma once

#include "ejff/gpu/device.hpp"

#include <memory>

#include <SDL3/SDL.h>

namespace ejff::gpu::resources
{

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

    explicit Sampler(Device &device, SDL_GPUFilter min_filter, SDL_GPUFilter mag_filter,
                     SDL_GPUSamplerMipmapMode mipmap_mode, SDL_GPUSamplerAddressMode address_mode_u,
                     SDL_GPUSamplerAddressMode address_mode_v,
                     SDL_GPUSamplerAddressMode address_mode_w, float mip_lod_bias,
                     float max_anisotropy, SDL_GPUCompareOp compare_op, float min_lod,
                     float max_lod, bool enable_anisotropy, bool enable_compare);

    Sampler(const Sampler &) = delete;
    Sampler &operator=(const Sampler &) = delete;

    Sampler(Sampler &&) noexcept = default;
    Sampler &operator=(Sampler &&) noexcept = default;

    ~Sampler() = default;

    void reset(SDL_GPUSampler *new_sampler = nullptr) noexcept { ptr_.reset(new_sampler); }

    SDL_GPUSampler *release() noexcept { return ptr_.release(); }

    explicit operator bool() const noexcept { return ptr_ != nullptr; }

    SDL_GPUSampler *get() noexcept { return ptr_.get(); }
    SDL_GPUSampler *get() const noexcept { return ptr_.get(); }

private:
    std::unique_ptr<SDL_GPUSampler, SDL_GPUSamplerDeleter> ptr_;
};

} // namespace ejff::gpu::resources
