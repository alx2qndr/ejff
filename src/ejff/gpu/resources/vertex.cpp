#include "ejff/gpu/resources/vertex.hpp"

namespace ejff::gpu
{

SDL_GPUVertexBufferDescription Vertex::getVertexBufferDescription()
{
    SDL_GPUVertexBufferDescription vertexBufferDescription{};
    vertexBufferDescription.slot = 0;
    vertexBufferDescription.pitch = sizeof(Vertex);
    vertexBufferDescription.input_rate = SDL_GPU_VERTEXINPUTRATE_VERTEX;
    return vertexBufferDescription;
}

std::array<SDL_GPUVertexAttribute, 4> Vertex::getVertexAttributes()
{
    std::array<SDL_GPUVertexAttribute, 4> vertexAttribute{};

    vertexAttribute[0].location = 0;
    vertexAttribute[0].buffer_slot = 0;
    vertexAttribute[0].format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3;
    vertexAttribute[0].offset = offsetof(Vertex, position);

    vertexAttribute[1].location = 1;
    vertexAttribute[1].buffer_slot = 0;
    vertexAttribute[1].format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT4;
    vertexAttribute[1].offset = offsetof(Vertex, color);

    vertexAttribute[2].location = 2;
    vertexAttribute[2].buffer_slot = 0;
    vertexAttribute[2].format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2;
    vertexAttribute[2].offset = offsetof(Vertex, uv);

    vertexAttribute[3].location = 3;
    vertexAttribute[3].buffer_slot = 0;
    vertexAttribute[3].format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3;
    vertexAttribute[3].offset = offsetof(Vertex, normal);

    return vertexAttribute;
}

} // namespace ejff::gpu