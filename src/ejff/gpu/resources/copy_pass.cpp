#include "ejff/gpu/resources/copy_pass.hpp"
#include "ejff/gpu/resources/buffer.hpp"
#include "ejff/gpu/resources/command_buffer.hpp"
#include "ejff/gpu/resources/texture.hpp"
#include "ejff/gpu/resources/transfer_buffer.hpp"

#include <stdexcept>

#include <fmt/format.h>

namespace ejff::gpu
{

CopyPass::CopyPass(CommandBuffer &command_buffer)
    : ptr_(create(command_buffer), SDL_GPUCopyPassDeleter{})
{
}

void CopyPass::uploadToBuffer(TransferBuffer &transferBuffer,
                              uint32_t sourceOffset, Buffer &buffer,
                              uint32_t destinationOffset, uint32_t size,
                              bool cycle)
{
    SDL_GPUTransferBufferLocation transferBufferLocation{};
    transferBufferLocation.transfer_buffer = transferBuffer.get();
    transferBufferLocation.offset = static_cast<Uint32>(sourceOffset);

    SDL_GPUBufferRegion bufferRegion{};
    bufferRegion.buffer = buffer.get();
    bufferRegion.offset = static_cast<Uint32>(destinationOffset);
    bufferRegion.size = static_cast<Uint32>(size);

    SDL_UploadToGPUBuffer(ptr_.get(), &transferBufferLocation, &bufferRegion,
                          cycle);
}

void CopyPass::uploadToTexture(TransferBuffer &transferBuffer, uint32_t offset,
                               uint32_t pixels_per_row, uint32_t rows_per_layer,
                               Texture &texture, uint32_t mipLevel,
                               uint32_t layer, uint32_t x, uint32_t y,
                               uint32_t z, uint32_t width, uint32_t height,
                               uint32_t depth, bool cycle)
{
    SDL_GPUTextureTransferInfo transferInfo{};
    transferInfo.transfer_buffer = transferBuffer.get();
    transferInfo.offset = static_cast<Uint32>(offset);
    transferInfo.pixels_per_row = pixels_per_row;
    transferInfo.rows_per_layer = rows_per_layer;

    SDL_GPUTextureRegion region{};
    region.texture = texture.get();
    region.mip_level = static_cast<Uint32>(mipLevel);
    region.layer = static_cast<Uint32>(layer);
    region.x = static_cast<Uint32>(x);
    region.y = static_cast<Uint32>(y);
    region.z = static_cast<Uint32>(z);
    region.w = static_cast<Uint32>(width);
    region.h = static_cast<Uint32>(height);
    region.d = static_cast<Uint32>(depth);

    SDL_UploadToGPUTexture(ptr_.get(), &transferInfo, &region, cycle);
}

void CopyPass::end()
{
    if (ptr_.get())
    {
        SDL_EndGPUCopyPass(ptr_.get());
    }
}

SDL_GPUCopyPass *CopyPass::create(CommandBuffer &commandBuffer)
{
    auto copyPass = SDL_BeginGPUCopyPass(commandBuffer.get());
    if (!copyPass)
    {
        throw std::runtime_error(fmt::format(
            "Couldn't create SDL_GPUCopyPass. SDL_BeginGPUCopyPass failed: {}",
            SDL_GetError()));
    }

    return copyPass;
}

} // namespace ejff::gpu