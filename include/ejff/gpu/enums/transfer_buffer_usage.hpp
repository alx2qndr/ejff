#pragma once

#include <SDL3/SDL.h>

namespace ejff::gpu
{

enum class TransferBufferUsage
{
    eUpload = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD,
    eDownload = SDL_GPU_TRANSFERBUFFERUSAGE_DOWNLOAD
};

} // namespace ejff::gpu