#include "ejff/gpu/resources/vertex.hpp"
#include <cstddef>

namespace ejff::gpu
{

const std::array<VertexAttribute, 4> Vertex::getAttributes()
{
    static const std::array<VertexAttribute, 4> attributes = {{
        {0, 0, VertexElementFormat::eFloat3, offsetof(Vertex, position)},
        {1, 0, VertexElementFormat::eFloat4, offsetof(Vertex, color)},
        {2, 0, VertexElementFormat::eFloat2, offsetof(Vertex, uv)},
        {3, 0, VertexElementFormat::eFloat3, offsetof(Vertex, normal)},
    }};

    return attributes;
}

const std::array<VertexBufferDescription, 1> Vertex::getBufferDescriptions()
{
    static const std::array<VertexBufferDescription, 1> bufferDescriptions = {
        {{0, sizeof(Vertex), VertexInputRate::eVertex, 0}}};

    return bufferDescriptions;
}

} // namespace ejff::gpu
