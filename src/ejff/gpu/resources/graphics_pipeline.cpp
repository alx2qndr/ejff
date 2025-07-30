#include "ejff/gpu/resources/graphics_pipeline.hpp"
#include "ejff/gpu/device.hpp"
#include "ejff/gpu/resources/render_pass.hpp"
#include "ejff/gpu/resources/shader.hpp"

#include <stdexcept>

#include <fmt/format.h>

namespace ejff::gpu
{

GraphicsPipeline::GraphicsPipeline(Device &device, Shader &vertexShader,
                                   Shader &fragmentShader,
                                   SDL_GPUVertexInputState vertexInputState,
                                   SDL_GPUPrimitiveType primitiveType,
                                   SDL_GPURasterizerState rasterizerState,
                                   SDL_GPUMultisampleState multisampleState,
                                   SDL_GPUDepthStencilState depthStencilState,
                                   SDL_GPUGraphicsPipelineTargetInfo targetInfo)
    : ptr_(create(device, vertexShader, fragmentShader, vertexInputState,
                  primitiveType, rasterizerState, multisampleState,
                  depthStencilState, targetInfo),
           SDL_GPUGraphicsPipelineDeleter{device.get()})
{
}

void GraphicsPipeline::bind(RenderPass &renderPass)
{
    if (!ptr_)
    {
        throw std::runtime_error("GraphicsPipeline is not initialized.");
    }

    SDL_BindGPUGraphicsPipeline(renderPass.get(), ptr_.get());
}

SDL_GPUGraphicsPipeline *GraphicsPipeline::create(
    Device &device, Shader &vertexShader, Shader &fragmentShader,
    SDL_GPUVertexInputState vertexInputState,
    SDL_GPUPrimitiveType primitiveType, SDL_GPURasterizerState rasterizerState,
    SDL_GPUMultisampleState multisampleState,
    SDL_GPUDepthStencilState depthStencilState,
    SDL_GPUGraphicsPipelineTargetInfo targetInfo)
{
    SDL_GPUGraphicsPipelineCreateInfo createInfo{};
    createInfo.vertex_shader = vertexShader.get();
    createInfo.fragment_shader = fragmentShader.get();
    createInfo.vertex_input_state = vertexInputState;
    createInfo.primitive_type = primitiveType;
    createInfo.rasterizer_state = rasterizerState;
    createInfo.multisample_state = multisampleState;
    createInfo.depth_stencil_state = depthStencilState;
    createInfo.target_info = targetInfo;

    auto graphicsPipeline =
        SDL_CreateGPUGraphicsPipeline(device.get(), &createInfo);
    if (!graphicsPipeline)
    {
        throw std::runtime_error(
            fmt::format("Couldn't create SDL_GPUGraphicsPipeline. "
                        "SDL_CreateGPUGraphicsPipeline failed: {}",
                        SDL_GetError()));
    }

    return graphicsPipeline;
}

} // namespace ejff::gpu