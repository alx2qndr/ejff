#pragma once

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

    explicit Sampler(Device &device, SDL_GPUFilter minFilter, SDL_GPUFilter magFilter,
                     SDL_GPUSamplerMipmapMode mipmapMode,
                     SDL_GPUSamplerAddressMode addressModeU,
                     SDL_GPUSamplerAddressMode addressModeV,
                     SDL_GPUSamplerAddressMode addressModeW, float mipLodBias,
                     float maxAnisotropy, SDL_GPUCompareOp compareOp, float minLod,
                     float maxLod, bool enableAnisotropy, bool enableCompare);

    Sampler(const Sampler &) = delete;
    Sampler &operator=(const Sampler &) = delete;

    Sampler(Sampler &&) noexcept = default;
    Sampler &operator=(Sampler &&) noexcept = default;

    ~Sampler() = default;

    SDL_GPUSampler *get() const noexcept { return ptr_.get(); }

private:
    SDL_GPUSampler *create(Device &device, SDL_GPUFilter minFilter,
                           SDL_GPUFilter magFilter, SDL_GPUSamplerMipmapMode mipmapMode,
                           SDL_GPUSamplerAddressMode addressModeU,
                           SDL_GPUSamplerAddressMode addressModeV,
                           SDL_GPUSamplerAddressMode addressModeW, float mipLodBias,
                           float maxAnisotropy, SDL_GPUCompareOp compareOp, float minLod,
                           float maxLod, bool enableAnisotropy, bool enableCompare);

    std::unique_ptr<SDL_GPUSampler, SDL_GPUSamplerDeleter> ptr_{nullptr};
};

} // namespace ejff::gpu
