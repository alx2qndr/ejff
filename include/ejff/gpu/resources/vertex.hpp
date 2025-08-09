#pragma once

#include "ejff/gpu/enums/vertex_element_format.hpp"
#include "ejff/gpu/enums/vertex_input_rate.hpp"

#include <array>
#include <vector>

#include <SDL3/SDL.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

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

struct Vertex
{
    glm::vec3 position{0.0f, 0.0f, 0.0f};
    glm::vec4 color{0.0f, 0.0f, 0.0f, 0.0f};
    glm::vec2 uv{0.0f, 0.0f};
    glm::vec3 normal{0.0f, 0.0f, 0.0f};

    static const std::array<VertexAttribute, 4> getAttributes();
    static const std::array<VertexBufferDescription, 1> getBufferDescriptions();
};

} // namespace ejff::gpu
