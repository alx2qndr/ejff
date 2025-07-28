#pragma once

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

    SDL_GPUGraphicsPipelineDeleter(SDL_GPUDevice *device = nullptr) : device(device) {}

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

    explicit GraphicsPipeline(Device &device, Shader &vertexShader,
                              Shader &fragmentShader,
                              SDL_GPUVertexInputState vertexInputState,
                              SDL_GPUPrimitiveType primitiveType,
                              SDL_GPURasterizerState rasterizerState,
                              SDL_GPUMultisampleState multisampleState,
                              SDL_GPUDepthStencilState depthStencilState,
                              SDL_GPUGraphicsPipelineTargetInfo targetInfo);

    GraphicsPipeline(const GraphicsPipeline &) = delete;
    GraphicsPipeline &operator=(const GraphicsPipeline &) = delete;

    GraphicsPipeline(GraphicsPipeline &&) noexcept = default;
    GraphicsPipeline &operator=(GraphicsPipeline &&) noexcept = default;

    ~GraphicsPipeline() = default;

    void bind(RenderPass &renderPass);

    SDL_GPUGraphicsPipeline *get() const noexcept { return ptr_.get(); }

private:
    SDL_GPUGraphicsPipeline *create(Device &device, Shader &vertexShader,
                                    Shader &fragmentShader,
                                    SDL_GPUVertexInputState vertexInputState,
                                    SDL_GPUPrimitiveType primitiveType,
                                    SDL_GPURasterizerState rasterizerState,
                                    SDL_GPUMultisampleState multisampleState,
                                    SDL_GPUDepthStencilState depthStencilState,
                                    SDL_GPUGraphicsPipelineTargetInfo targetInfo);

    std::unique_ptr<SDL_GPUGraphicsPipeline, SDL_GPUGraphicsPipelineDeleter> ptr_{
        nullptr};
};

} // namespace ejff::gpu
