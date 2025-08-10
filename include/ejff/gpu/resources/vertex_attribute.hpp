#pragma once

#include "ejff/gpu/enums/vertex_element_format.hpp"

#include <SDL3/SDL.h>

namespace ejff::gpu
{

struct VertexAttribute
{
    uint32_t location = 0;
    uint32_t buffer_slot = 0;
    VertexElementFormat format = VertexElementFormat::eInvalid;
    uint32_t offset = 0;

    SDL_GPUVertexAttribute get() const
    {
        SDL_GPUVertexAttribute attribute{};
        attribute.location = static_cast<Uint32>(location);
        attribute.buffer_slot = static_cast<Uint32>(buffer_slot);
        attribute.format = static_cast<SDL_GPUVertexElementFormat>(format);
        attribute.offset = static_cast<Uint32>(offset);

        return attribute;
    }
};

} // namespace ejff::gpu
