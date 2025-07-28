#pragma once

#include "ejff/gpu/device.hpp"
#include "ejff/gpu/resources/render_pass.hpp"
#include "ejff/gpu/resources/shader.hpp"
#include "ejff/window.hpp"

#include <memory>

#include <SDL3/SDL.h>

namespace ejff::gpu
{

struct SDL_GPUGraphicsPipelineDeleter
{
    SDL_GPUDevice *device;

    SDL_GPUGraphicsPipelineDeleter(SDL_GPUDevice *device = nullptr) : device(device) {}

    void operator()(SDL_GPUGraphicsPipeline *graphics_pipeline) const noexcept
    {
        if (graphics_pipeline)
        {
            SDL_ReleaseGPUGraphicsPipeline(device, graphics_pipeline);
        }
    }
};

class GraphicsPipeline
{
public:
    GraphicsPipeline() = default;

    explicit GraphicsPipeline(Device &device, Shader &vertex_shader, Shader &fragment_shader,
                              SDL_GPUVertexInputState vertex_input_state,
                              SDL_GPUPrimitiveType primitive_type,
                              SDL_GPURasterizerState rasterizer_state,
                              SDL_GPUMultisampleState multisample_state,
                              SDL_GPUDepthStencilState depth_stencil_state,
                              SDL_GPUGraphicsPipelineTargetInfo target_info);

    GraphicsPipeline(const GraphicsPipeline &) = delete;
    GraphicsPipeline &operator=(const GraphicsPipeline &) = delete;

    GraphicsPipeline(GraphicsPipeline &&) noexcept = default;
    GraphicsPipeline &operator=(GraphicsPipeline &&) noexcept = default;

    ~GraphicsPipeline() = default;

    static GraphicsPipeline create_default_pipeline(Device &device, Shader &vertex_shader,
                                                    Shader &fragment_shader, Window &window);

    void bind(RenderPass &render_pass);

    void reset(SDL_GPUGraphicsPipeline *new_graphics_pipeline = nullptr) noexcept
    {
        ptr_.reset(new_graphics_pipeline);
    }

    SDL_GPUGraphicsPipeline *release() noexcept { return ptr_.release(); }

    SDL_GPUGraphicsPipeline *get() noexcept { return ptr_.get(); }
    
    SDL_GPUGraphicsPipeline *get() const noexcept { return ptr_.get(); }

    explicit operator bool() const noexcept { return ptr_ != nullptr; }

private:
    std::unique_ptr<SDL_GPUGraphicsPipeline, SDL_GPUGraphicsPipelineDeleter> ptr_;
};

} // namespace ejff::gpu
