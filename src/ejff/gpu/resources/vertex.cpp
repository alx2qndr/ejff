#include "ejff/gpu/resources/vertex.hpp"

namespace ejff::gpu::resources
{

SDL_GPUVertexBufferDescription Vertex::get_vertex_buffer_description()
{
    SDL_GPUVertexBufferDescription vertex_buffer_description{};
    vertex_buffer_description.slot = 0;
    vertex_buffer_description.pitch = sizeof(Vertex);
    vertex_buffer_description.input_rate = SDL_GPU_VERTEXINPUTRATE_VERTEX;
    return vertex_buffer_description;
}

std::array<SDL_GPUVertexAttribute, 4> Vertex::get_vertex_attributes()
{
    std::array<SDL_GPUVertexAttribute, 4> vertex_attribute{};

    vertex_attribute[0].location = 0;
    vertex_attribute[0].buffer_slot = 0;
    vertex_attribute[0].format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3;
    vertex_attribute[0].offset = offsetof(Vertex, position);

    vertex_attribute[1].location = 1;
    vertex_attribute[1].buffer_slot = 0;
    vertex_attribute[1].format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT4;
    vertex_attribute[1].offset = offsetof(Vertex, color);

    vertex_attribute[2].location = 2;
    vertex_attribute[2].buffer_slot = 0;
    vertex_attribute[2].format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2;
    vertex_attribute[2].offset = offsetof(Vertex, uv);

    vertex_attribute[3].location = 3;
    vertex_attribute[3].buffer_slot = 0;
    vertex_attribute[3].format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3;
    vertex_attribute[3].offset = offsetof(Vertex, normal);

    return vertex_attribute;
}

} // namespace ejff::gpu::resources