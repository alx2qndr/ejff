#pragma once

#include "ejff/gpu/resources/vertex.hpp"

#include <vector>

#include <SDL3/SDL.h>

namespace ejff::gpu
{

struct VertexInputState
{
    const VertexBufferDescription *pBufferDescriptions = nullptr;
    uint32_t bufferCount = 0;
    const VertexAttribute *pAttributes = nullptr;
    uint32_t attributesCount = 0;

    SDL_GPUVertexInputState get() const
    {
        static std::vector<SDL_GPUVertexBufferDescription> bufferDescription;
        static std::vector<SDL_GPUVertexAttribute> attributes;

        bufferDescription.clear();
        attributes.clear();

        for (uint32_t i = 0; i < bufferCount; ++i)
        {
            bufferDescription.push_back(pBufferDescriptions[i].get());
        }

        for (uint32_t i = 0; i < attributesCount; ++i)
        {
            attributes.push_back(pAttributes[i].get());
        }

        SDL_GPUVertexInputState inputState{};
        inputState.vertex_buffer_descriptions = bufferDescription.data();
        inputState.num_vertex_buffers =
            static_cast<Uint32>(bufferDescription.size());
        inputState.vertex_attributes = attributes.data();
        inputState.num_vertex_attributes =
            static_cast<Uint32>(attributes.size());

        return inputState;
    }
};

} // namespace ejff::gpu
