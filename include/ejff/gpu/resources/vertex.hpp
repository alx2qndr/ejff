#pragma once

#include <array>
#include <vector>

#include <SDL3/SDL.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace ejff::gpu
{

struct Vertex
{
    enum class InputRate
    {
        eVertex = SDL_GPU_VERTEXINPUTRATE_VERTEX,
        eInstance = SDL_GPU_VERTEXINPUTRATE_INSTANCE
    };

    enum class ElementFormat : uint64_t
    {
        eInvalid = SDL_GPU_VERTEXELEMENTFORMAT_INVALID,

        eInt = SDL_GPU_VERTEXELEMENTFORMAT_INT,
        eInt2 = SDL_GPU_VERTEXELEMENTFORMAT_INT2,
        eInt3 = SDL_GPU_VERTEXELEMENTFORMAT_INT3,
        eInt4 = SDL_GPU_VERTEXELEMENTFORMAT_INT4,

        eUInt = SDL_GPU_VERTEXELEMENTFORMAT_UINT,
        eUInt2 = SDL_GPU_VERTEXELEMENTFORMAT_UINT2,
        eUInt3 = SDL_GPU_VERTEXELEMENTFORMAT_UINT3,
        eUInt4 = SDL_GPU_VERTEXELEMENTFORMAT_UINT4,

        eFloat = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT,
        eFloat2 = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2,
        eFloat3 = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3,
        eFloat4 = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT4,

        eByte2 = SDL_GPU_VERTEXELEMENTFORMAT_BYTE2,
        eByte4 = SDL_GPU_VERTEXELEMENTFORMAT_BYTE4,

        eUByte2 = SDL_GPU_VERTEXELEMENTFORMAT_UBYTE2,
        eUByte4 = SDL_GPU_VERTEXELEMENTFORMAT_UBYTE4,

        eByte2Norm = SDL_GPU_VERTEXELEMENTFORMAT_BYTE2_NORM,
        eByte4Norm = SDL_GPU_VERTEXELEMENTFORMAT_BYTE4_NORM,

        eUByte2Norm = SDL_GPU_VERTEXELEMENTFORMAT_UBYTE2_NORM,
        eUByte4Norm = SDL_GPU_VERTEXELEMENTFORMAT_UBYTE4_NORM,

        eShort2 = SDL_GPU_VERTEXELEMENTFORMAT_SHORT2,
        eShort4 = SDL_GPU_VERTEXELEMENTFORMAT_SHORT4,

        eUShort2 = SDL_GPU_VERTEXELEMENTFORMAT_USHORT2,
        eUShort4 = SDL_GPU_VERTEXELEMENTFORMAT_USHORT4,

        eShort2Norm = SDL_GPU_VERTEXELEMENTFORMAT_SHORT2_NORM,
        eShort4Norm = SDL_GPU_VERTEXELEMENTFORMAT_SHORT4_NORM,

        eUShort2Norm = SDL_GPU_VERTEXELEMENTFORMAT_USHORT2_NORM,
        eUShort4Norm = SDL_GPU_VERTEXELEMENTFORMAT_USHORT4_NORM,

        eHalf2 = SDL_GPU_VERTEXELEMENTFORMAT_HALF2,
        eHalf4 = SDL_GPU_VERTEXELEMENTFORMAT_HALF4
    };

    struct Attribute
    {
        uint32_t location = 0;
        uint32_t buffer_slot = 0;
        ElementFormat format = ElementFormat::eInvalid;
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

    struct BufferDescription
    {
        uint32_t slot = 0;
        uint32_t pitch = 0;
        InputRate inputRate{};
        uint32_t instanceStepRate = 0;

        const SDL_GPUVertexBufferDescription get() const
        {
            SDL_GPUVertexBufferDescription bufferDescription{};
            bufferDescription.slot = static_cast<Uint32>(slot);
            bufferDescription.pitch = static_cast<Uint32>(pitch);
            bufferDescription.input_rate =
                static_cast<SDL_GPUVertexInputRate>(inputRate);
            bufferDescription.instance_step_rate =
                static_cast<Uint32>(instanceStepRate);

            return bufferDescription;
        }
    };

    struct InputState
    {
        const BufferDescription *pBufferDescriptions = nullptr;
        uint32_t bufferCount = 0;
        const Attribute *pAttributes = nullptr;
        uint32_t attributesCount = 0;

        SDL_GPUVertexInputState get() const
        {
            static std::vector<SDL_GPUVertexBufferDescription>
                bufferDescription;
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

    glm::vec3 position{0.0f, 0.0f, 0.0f};
    glm::vec4 color{0.0f, 0.0f, 0.0f, 0.0f};
    glm::vec2 uv{0.0f, 0.0f};
    glm::vec3 normal{0.0f, 0.0f, 0.0f};

    static const std::array<Attribute, 4> getAttributes();
    static const std::array<BufferDescription, 1> getBufferDescriptions();
};

} // namespace ejff::gpu
