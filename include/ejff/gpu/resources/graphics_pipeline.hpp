#pragma once

#include "ejff/gpu/resources/graphics_pipeline_target_info.hpp"

#include "ejff/gpu/resources/texture.hpp"

#include "ejff/gpu/resources/states/depth_stencil_state.hpp"
#include "ejff/gpu/resources/states/multisample_state.hpp"
#include "ejff/gpu/resources/states/rasterizer_state.hpp"
#include "ejff/gpu/resources/states/vertex_input_state.hpp"

#include "ejff/gpu/enums/primitive_type.hpp"

#include <memory>

#include <SDL3/SDL.h>

namespace ejff::gpu
{

class Device;
class RenderPass;
class Shader;

struct SDL_GPUGraphicsPipelineDeleter
{
    SDL_GPUDevice *device;

    SDL_GPUGraphicsPipelineDeleter(SDL_GPUDevice *device = nullptr)
        : device(device)
    {
    }

    void operator()(SDL_GPUGraphicsPipeline *graphicsPipeline) const noexcept
    {
        if (graphicsPipeline)
        {
            SDL_ReleaseGPUGraphicsPipeline(device, graphicsPipeline);
        }
    }
};

class GraphicsPipeline
{
public:
    GraphicsPipeline() = default;

    explicit GraphicsPipeline(
        Device &device, Shader &vertexShader, Shader &fragmentShader,
        VertexInputState vertexInputState, PrimitiveType primitiveType,
        RasterizerState rasterizerState, MultisampleState multisampleState,
        DepthStencilState depthStencilState, GraphicsPipelineTargetInfo targetInfo);

    GraphicsPipeline(const GraphicsPipeline &) = delete;
    GraphicsPipeline &operator=(const GraphicsPipeline &) = delete;

    GraphicsPipeline(GraphicsPipeline &&) noexcept = default;
    GraphicsPipeline &operator=(GraphicsPipeline &&) noexcept = default;

    ~GraphicsPipeline() = default;

    void bind(RenderPass &renderPass);

    SDL_GPUGraphicsPipeline *get() const noexcept { return ptr_.get(); }

private:
    SDL_GPUGraphicsPipeline *create(
        Device &device, Shader &vertexShader, Shader &fragmentShader,
        VertexInputState vertexInputState, PrimitiveType primitiveType,
        RasterizerState rasterizerState, MultisampleState multisampleState,
        DepthStencilState depthStencilState, GraphicsPipelineTargetInfo targetInfo);

    std::unique_ptr<SDL_GPUGraphicsPipeline, SDL_GPUGraphicsPipelineDeleter>
        ptr_{nullptr};
};

} // namespace ejff::gpu
