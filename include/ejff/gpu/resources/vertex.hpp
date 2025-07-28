#pragma once

#include <array>

#include <SDL3/SDL.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace ejff::gpu
{

struct Vertex
{
    glm::vec3 position{0.0f};
    glm::vec4 color{0.0f};
    glm::vec2 uv{0.0f};
    glm::vec3 normal{0.0f};

    static SDL_GPUVertexBufferDescription getVertexBufferDescription();
    static std::array<SDL_GPUVertexAttribute, 4> getVertexAttributes();
};

} // namespace ejff::gpu