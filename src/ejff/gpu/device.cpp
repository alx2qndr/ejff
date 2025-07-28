#include "ejff/gpu/device.hpp"

#include <stdexcept>

#include <fmt/format.h>

namespace ejff::gpu
{

Device::Device(Shader::Format formatFlags, bool debug, const char *driver)
    : ptr_(nullptr, SDL_GPUDeviceDeleter{})
{
    auto device = SDL_CreateGPUDevice(static_cast<Uint8>(formatFlags), debug, driver);
    if (!device)
    {
        throw std::runtime_error(
            fmt::format("Couldn't create SDL_GPUDevice. SDL_CreateGPUDevice failed: {}",
                        SDL_GetError()));
    }

    ptr_.reset(device);
}

} // namespace ejff::gpu