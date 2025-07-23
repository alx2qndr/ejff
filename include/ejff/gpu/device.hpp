#pragma once

#include <memory>

#include <SDL3/SDL.h>

namespace ejff::gpu
{

struct SDL_GPUDeviceDeleter
{
    void operator()(SDL_GPUDevice *device) const noexcept
    {
        if (device)
        {
            SDL_DestroyGPUDevice(device);
        }
    }
};

class Device
{
public:
    Device() = default;

    explicit Device(SDL_GPUShaderFormat format, bool debug_mode, const char *name);

    Device(const Device &) = delete;
    Device &operator=(const Device &) = delete;

    Device(Device &&) noexcept = default;
    Device &operator=(Device &&) noexcept = default;

    ~Device() = default;

    void reset(SDL_GPUDevice *new_device = nullptr) noexcept { ptr_.reset(new_device); }

    SDL_GPUDevice *release() noexcept { return ptr_.release(); }

    explicit operator bool() const noexcept { return ptr_ != nullptr; }

    SDL_GPUDevice *get() noexcept { return ptr_.get(); }
    SDL_GPUDevice *get() const noexcept { return ptr_.get(); }

private:
    std::unique_ptr<SDL_GPUDevice, SDL_GPUDeviceDeleter> ptr_;
};

} // namespace ejff::gpu
