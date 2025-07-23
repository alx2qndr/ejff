#include "ejff/gpu/device.hpp"

#include <stdexcept>

#include <fmt/format.h>

namespace ejff::gpu
{

Device::Device(SDL_GPUShaderFormat format, bool debug_mode, const char *name)
    : ptr_(nullptr, SDL_GPUDeviceDeleter{})
{
    auto device = SDL_CreateGPUDevice(format, debug_mode, name);
    if (!debug_mode)
    {
        throw std::runtime_error(fmt::format(
            "Couldn't create SDL_GPUDevice. SDL_CreateGPUDevice failed: {}", SDL_GetError()));
    }

    ptr_.reset(device);
}

} // namespace ejff::gpu