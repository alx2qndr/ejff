#include "ejff/gpu/resources/copy_pass.hpp"

#include <stdexcept>

#include <fmt/format.h>

namespace ejff::gpu
{

CopyPass::CopyPass(CommandBuffer &command_buffer) : ptr_(nullptr, SDL_GPUCopyPassDeleter{})
{
    auto copy_pass = SDL_BeginGPUCopyPass(command_buffer.get());
    if (!copy_pass)
    {
        throw std::runtime_error(fmt::format(
            "Couldn't create SDL_GPUCopyPass. SDL_BeginGPUCopyPass failed: {}", SDL_GetError()));
    }

    ptr_.reset(copy_pass);
}

void CopyPass::upload_to_buffer(SDL_GPUTransferBufferLocation source,
                                SDL_GPUBufferRegion destination, bool cycle)
{
    SDL_UploadToGPUBuffer(ptr_.get(), &source, &destination, cycle);
}

void CopyPass::upload_to_texture(SDL_GPUTextureTransferInfo source,
                                 SDL_GPUTextureRegion destination, bool cycle)
{
    SDL_UploadToGPUTexture(ptr_.get(), &source, &destination, cycle);
}

} // namespace ejff::gpu