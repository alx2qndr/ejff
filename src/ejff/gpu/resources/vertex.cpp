#include "ejff/gpu/resources/vertex.hpp"

#include <cstddef> // offsetof

namespace ejff::gpu
{

const std::array<VertexAttribute, 4> Vertex::getAttributes()
{
    static const std::array<VertexAttribute, 4> attributes = [] {
        std::array<VertexAttribute, 4> attr{};

        attr[0].location = 0;
        attr[0].buffer_slot = 0;
        attr[0].format = VertexElementFormat::eFloat3;
        attr[0].offset = offsetof(Vertex, position);

        attr[1].location = 1;
        attr[1].buffer_slot = 0;
        attr[1].format = VertexElementFormat::eFloat4;
        attr[1].offset = offsetof(Vertex, color);

        attr[2].location = 2;
        attr[2].buffer_slot = 0;
        attr[2].format = VertexElementFormat::eFloat2;
        attr[2].offset = offsetof(Vertex, uv);

        attr[3].location = 3;
        attr[3].buffer_slot = 0;
        attr[3].format = VertexElementFormat::eFloat3;
        attr[3].offset = offsetof(Vertex, normal);

        return attr;
    }();

    return attributes;
}

const std::array<VertexBufferDescription, 1> Vertex::getBufferDescriptions()
{
    static const std::array<VertexBufferDescription, 1> bufferDescriptions =
        [] {
            std::array<VertexBufferDescription, 1> bufDesc{};

            bufDesc[0].slot = 0;
            bufDesc[0].pitch = sizeof(Vertex);
            bufDesc[0].input_rate = VertexInputRate::eVertex;
            bufDesc[0].instance_step_rate = 0;

            return bufDesc;
        }();

    return bufferDescriptions;
}

} // namespace ejff::gpu
