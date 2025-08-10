#pragma once

#include "ejff/gpu/enums/vertex_input_rate.hpp"

#include <SDL3/SDL.h>

namespace ejff::gpu
{

struct VertexBufferDescription
{
    uint32_t slot = 0;
    uint32_t pitch = 0;
    VertexInputRate input_rate = VertexInputRate::eVertex;
    uint32_t instance_step_rate = 0;

    SDL_GPUVertexBufferDescription get() const
    {
        SDL_GPUVertexBufferDescription desc{};
        desc.slot = static_cast<Uint32>(slot);
        desc.pitch = static_cast<Uint32>(pitch);
        desc.input_rate = static_cast<SDL_GPUVertexInputRate>(input_rate);
        desc.instance_step_rate = static_cast<Uint32>(instance_step_rate);

        return desc;
    }
};

} // namespace ejff::gpu
