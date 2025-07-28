#pragma once

#include "ejff/gpu/resources/command_buffer.hpp"

#include <memory>

#include <SDL3/SDL.h>

namespace ejff::gpu
{

struct SDL_GPUCopyPassDeleter
{
    void operator()(SDL_GPUCopyPass *copy_pass) const noexcept
    {
        if (copy_pass)
        {
            SDL_EndGPUCopyPass(copy_pass);
        }
    }
};

class CopyPass
{
public:
    CopyPass() = default;

    explicit CopyPass(CommandBuffer &command_buffer);

    CopyPass(const CopyPass &) = delete;
    CopyPass &operator=(const CopyPass &) = delete;

    CopyPass(CopyPass &&) noexcept = default;
    CopyPass &operator=(CopyPass &&) noexcept = default;

    ~CopyPass() = default;

    void upload_to_buffer(SDL_GPUTransferBufferLocation source, SDL_GPUBufferRegion destination,
                          bool cycle = false);

    void upload_to_texture(SDL_GPUTextureTransferInfo source, SDL_GPUTextureRegion destination,
                           bool cycle = false);

    void reset(SDL_GPUCopyPass *new_copy_pass = nullptr) noexcept { ptr_.reset(new_copy_pass); }

    SDL_GPUCopyPass *release() noexcept { return ptr_.release(); }

    SDL_GPUCopyPass *get() noexcept { return ptr_.get(); }

    SDL_GPUCopyPass *get() const noexcept { return ptr_.get(); }

    explicit operator bool() const noexcept { return ptr_ != nullptr; }

private:
    std::unique_ptr<SDL_GPUCopyPass, SDL_GPUCopyPassDeleter> ptr_;
};

} // namespace ejff::gpu
