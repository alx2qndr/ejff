#include "ejff/gpu/resources/graphics_pipeline.hpp"
#include "ejff/gpu/resources/vertex.hpp"

#include <stdexcept>

#include <fmt/format.h>

namespace ejff::gpu
{

GraphicsPipeline::GraphicsPipeline(Device &device, Shader &vertex_shader, Shader &fragment_shader,
                                   SDL_GPUVertexInputState vertex_input_state,
                                   SDL_GPUPrimitiveType primitive_type,
                                   SDL_GPURasterizerState rasterizer_state,
                                   SDL_GPUMultisampleState multisample_state,
                                   SDL_GPUDepthStencilState depth_stencil_state,
                                   SDL_GPUGraphicsPipelineTargetInfo target_info)
    : ptr_(nullptr, SDL_GPUGraphicsPipelineDeleter{device.get()})
{
    SDL_GPUGraphicsPipelineCreateInfo createinfo{};
    createinfo.vertex_shader = vertex_shader.get();
    createinfo.fragment_shader = fragment_shader.get();
    createinfo.vertex_input_state = vertex_input_state;
    createinfo.primitive_type = primitive_type;
    createinfo.rasterizer_state = rasterizer_state;
    createinfo.multisample_state = multisample_state;
    createinfo.depth_stencil_state = depth_stencil_state;
    createinfo.target_info = target_info;
    createinfo.props = {};

    auto graphics_pipeline = SDL_CreateGPUGraphicsPipeline(device.get(), &createinfo);
    if (!graphics_pipeline)
    {
        throw std::runtime_error(fmt::format(
            "Couldn't create SDL_GPUGraphicsPipeline. SDL_CreateGPUGraphicsPipeline failed: {}",
            SDL_GetError()));
    }

    ptr_.reset(graphics_pipeline);
}

GraphicsPipeline GraphicsPipeline::create_default_pipeline(Device &device, Shader &vertex_shader,
                                                           Shader &fragment_shader, Window &window)
{
    SDL_GPUColorTargetDescription color_target_description{};
    color_target_description.format = SDL_GetGPUSwapchainTextureFormat(device.get(), window.get());

    auto vertex_attributes = Vertex::get_vertex_attributes();
    auto vertex_buffer_description = Vertex::get_vertex_buffer_description();

    SDL_GPUVertexInputState vertex_input_state{};
    vertex_input_state.vertex_buffer_descriptions = &vertex_buffer_description;
    vertex_input_state.num_vertex_buffers = 1;
    vertex_input_state.vertex_attributes = vertex_attributes.data();
    vertex_input_state.num_vertex_attributes = static_cast<Uint32>(vertex_attributes.size());

    SDL_GPURasterizerState rasterizer_state{};
    SDL_GPUMultisampleState multisample_state{};
    SDL_GPUDepthStencilState depth_stencil_state{};

    SDL_GPUGraphicsPipelineTargetInfo target_info{};
    target_info.color_target_descriptions = &color_target_description;
    target_info.num_color_targets = 1;

    return GraphicsPipeline(device, vertex_shader, fragment_shader, vertex_input_state,
                            SDL_GPU_PRIMITIVETYPE_TRIANGLELIST, rasterizer_state, multisample_state,
                            depth_stencil_state, target_info);
}

void GraphicsPipeline::bind(RenderPass &render_pass)
{
    if (!ptr_)
    {
        throw std::runtime_error("GraphicsPipeline is not initialized.");
    }

    SDL_BindGPUGraphicsPipeline(render_pass.get(), ptr_.get());
}

} // namespace ejff::gpu