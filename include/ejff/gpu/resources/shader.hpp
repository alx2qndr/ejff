#pragma once

#include "ejff/gpu/device.hpp"

#include <filesystem>
#include <memory>

#include <SDL3/SDL.h>

namespace ejff::gpu
{

struct SDL_GPUShaderDeleter
{
    SDL_GPUDevice *device;

    SDL_GPUShaderDeleter(SDL_GPUDevice *device = nullptr) : device(device) {}

    void operator()(SDL_GPUShader *shader) const noexcept
    {
        if (shader)
        {
            SDL_ReleaseGPUShader(device, shader);
        }
    }
};

class Shader
{
public:
    Shader() = default;

    explicit Shader(Device &device, const std::filesystem::path &path,
                    Uint32 num_samplers = 0, Uint32 num_storage_textures = 0,
                    Uint32 num_storage_buffers = 0, Uint32 num_uniform_buffers = 0);

    Shader(const Shader &) = delete;
    Shader &operator=(const Shader &) = delete;

    Shader(Shader &&) noexcept = default;
    Shader &operator=(Shader &&) noexcept = default;

    ~Shader() = default;

    void reset(SDL_GPUShader *new_shader = nullptr) noexcept { ptr_.reset(new_shader); }

    SDL_GPUShader *release() noexcept { return ptr_.release(); }

    SDL_GPUShader *get() noexcept { return ptr_.get(); }

    SDL_GPUShader *get() const noexcept { return ptr_.get(); }

    explicit operator bool() const noexcept { return ptr_ != nullptr; }

private:
    std::unique_ptr<SDL_GPUShader, SDL_GPUShaderDeleter> ptr_;
};

} // namespace ejff::gpu
