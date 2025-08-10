#pragma once

#include "ejff/gpu/resources/vertex_attribute.hpp"
#include "ejff/gpu/resources/vertex_buffer_description.hpp"

#include <array>

#include <SDL3/SDL.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace ejff::gpu
{

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
