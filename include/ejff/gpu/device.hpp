#pragma once

#include "ejff/gpu/resources/shader.hpp"

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
    std::unique_ptr<SDL_GPUDevice, SDL_GPUDeviceDeleter> ptr_;

    Device() = default;

    explicit Device(Shader::Format formatFlags, bool debug, const char *driver);

    Device(const Device &) = delete;
    Device &operator=(const Device &) = delete;

    Device(Device &&) noexcept = default;
    Device &operator=(Device &&) noexcept = default;

    ~Device() = default;

    void reset(SDL_GPUDevice *new_device = nullptr) noexcept { ptr_.reset(new_device); }

    SDL_GPUDevice *release() noexcept { return ptr_.release(); }

    SDL_GPUDevice *get() noexcept { return ptr_.get(); }

    SDL_GPUDevice *get() const noexcept { return ptr_.get(); }

    explicit operator bool() const noexcept { return ptr_ != nullptr; }
};

} // namespace ejff::gpu
