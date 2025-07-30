#include "ejff/gpu/resources/vertex.hpp"

#include <cstddef>

namespace ejff::gpu
{

const std::array<Vertex::Attribute, 4> Vertex::getAttributes()
{
    static const std::array<Vertex::Attribute, 4> attributes = [] {
        std::array<Vertex::Attribute, 4> attr{};
        attr[0].location = 0;
        attr[0].buffer_slot = 0;
        attr[0].format = Vertex::ElementFormat::eFloat3;
        attr[0].offset = offsetof(Vertex, position);

        attr[1].location = 1;
        attr[1].buffer_slot = 0;
        attr[1].format = Vertex::ElementFormat::eFloat4;
        attr[1].offset = offsetof(Vertex, color);

        attr[2].location = 2;
        attr[2].buffer_slot = 0;
        attr[2].format = Vertex::ElementFormat::eFloat2;
        attr[2].offset = offsetof(Vertex, uv);

        attr[3].location = 3;
        attr[3].buffer_slot = 0;
        attr[3].format = Vertex::ElementFormat::eFloat3;
        attr[3].offset = offsetof(Vertex, normal);

        return attr;
    }();

    return attributes;
}

const std::array<Vertex::BufferDescription, 1> Vertex::getBufferDescriptions()
{
    static const std::array<Vertex::BufferDescription, 1> bufferDescriptions =
        [] {
            std::array<Vertex::BufferDescription, 1> bufferDescriptions{};
            bufferDescriptions[0].slot = 0;
            bufferDescriptions[0].pitch = sizeof(Vertex);
            bufferDescriptions[0].inputRate = Vertex::InputRate::eVertex;
            bufferDescriptions[0].instanceStepRate = 0;
            return bufferDescriptions;
        }();

    return bufferDescriptions;
}

} // namespace ejff::gpu
