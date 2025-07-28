#pragma once

#include <memory>

#include <SDL3/SDL.h>

namespace ejff::gpu
{

class Buffer;
class CommandBuffer;
class Texture;
class TransferBuffer;

struct SDL_GPUCopyPassDeleter
{
    void operator()(SDL_GPUCopyPass *copyPass) const noexcept
    {
        if (copyPass)
        {
            SDL_EndGPUCopyPass(copyPass);
        }
    }
};

class CopyPass
{
public:
    CopyPass() = default;

    explicit CopyPass(CommandBuffer &commandBuffer);

    CopyPass(const CopyPass &) = delete;
    CopyPass &operator=(const CopyPass &) = delete;

    CopyPass(CopyPass &&) noexcept = default;
    CopyPass &operator=(CopyPass &&) noexcept = default;

    ~CopyPass() = default;

    void uploadToBuffer(TransferBuffer &transferBuffer, uint32_t sourceOffset,
                        Buffer &buffer, uint32_t destinationOffset, uint32_t size,
                        bool cycle = false);

    void uploadToTexture(TransferBuffer &transferBuffer, uint32_t offset,
                         uint32_t pixels_per_row, uint32_t rows_per_layer,
                         Texture &texture, uint32_t mipLevel, uint32_t layer, uint32_t x,
                         uint32_t y, uint32_t z, uint32_t width, uint32_t height,
                         uint32_t depth, bool cycle = false);

    void end();

    SDL_GPUCopyPass *get() const noexcept { return ptr_.get(); }

private:
    SDL_GPUCopyPass *create(CommandBuffer &commandBuffer);

    std::unique_ptr<SDL_GPUCopyPass, SDL_GPUCopyPassDeleter> ptr_{nullptr};
};

} // namespace ejff::gpu
