#include "ejff/application.hpp"

#include "ejff/gpu/resources/command_buffer.hpp"
#include "ejff/gpu/resources/copy_pass.hpp"
#include "ejff/gpu/resources/render_pass.hpp"
#include "ejff/gpu/resources/shader.hpp"
#include "ejff/gpu/resources/transfer_buffer.hpp"
#include "ejff/gpu/resources/vertex.hpp"
#include "ejff/surface.hpp"

#include <iostream>
#include <vector>

#include <fmt/format.h>

namespace ejff
{

std::vector<gpu::Vertex> vertices = {
    {
        {0.5f, -0.5f, 0.0f},
        {1.0f, 0.0f, 0.0f, 1.0f},
        {1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f},
    },
    {
        {-0.5f, -0.5f, 0.0f},
        {0.0f, 1.0f, 0.0f, 1.0f},
        {0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f},
    },
    {
        {0.5f, 0.5f, 0.0f},
        {0.0f, 0.0f, 1.0f, 1.0f},
        {1.0f, 1.0f},
        {0.0f, 0.0f, 1.0f},
    },
    {
        {-0.5f, 0.5f, 0.0f},
        {1.0f, 1.0f, 0.0f, 1.0f},
        {0.0f, 1.0f},
        {0.0f, 0.0f, 1.0f},
    },
};

std::vector<Uint32> indices = {0, 1, 2, 2, 1, 3};

void Application::init(int argc, char **argv)
{
    std::vector<std::string_view> args(argv, argv + argc);

    for (const auto &arg : args)
    {
        std::cout << arg << '\n';
    }

    window_ = Window("Hello, Engine Just For Fun (EJFF for short)!", 1280, 720,
                     Window::Flags::eResizable | Window::Flags::eHighPixelDensity);

    device_ = gpu::Device(gpu::Shader::Format::eSPIRV | gpu::Shader::Format::eMSL |
                              gpu::Shader::Format::eDXIL,
                          true, nullptr);

    if (!SDL_ClaimWindowForGPUDevice(device_.get(), window_.get()))
    {
        throw std::runtime_error(
            fmt::format("Couldn't claim SDL_GPUWindow for SDL_GPUDevice. "
                        "SDL_ClaimWindowForGPUDevice failed: {}",
                        SDL_GetError()));
    }

    auto vertexShader = gpu::Shader(device_, "../shaders/src/triangle.vert", 0, 0, 0, 0);
    auto fragmentShader =
        gpu::Shader(device_, "../shaders/src/triangle.frag", 1, 0, 0, 0);

    auto vertexAttributes = gpu::Vertex::getVertexAttributes();
    auto vertexBufferDescription = gpu::Vertex::getVertexBufferDescription();

    SDL_GPUVertexInputState vertexInputState{};
    vertexInputState.vertex_buffer_descriptions = &vertexBufferDescription;
    vertexInputState.num_vertex_buffers = 1;
    vertexInputState.vertex_attributes = vertexAttributes.data();
    vertexInputState.num_vertex_attributes = static_cast<Uint32>(vertexAttributes.size());

    SDL_GPURasterizerState rasterizerState{};
    rasterizerState.fill_mode = SDL_GPU_FILLMODE_FILL;
    rasterizerState.cull_mode = SDL_GPU_CULLMODE_BACK;
    rasterizerState.front_face = SDL_GPU_FRONTFACE_CLOCKWISE;

    SDL_GPUMultisampleState multisampleState{};
    multisampleState.sample_count = SDL_GPU_SAMPLECOUNT_1;

    SDL_GPUDepthStencilState depthStencilState{};
    depthStencilState.enable_depth_test = false;

    SDL_GPUColorTargetBlendState colorTargetBlendState{};
    colorTargetBlendState.src_color_blendfactor = SDL_GPU_BLENDFACTOR_SRC_ALPHA;
    colorTargetBlendState.dst_color_blendfactor = SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA;
    colorTargetBlendState.color_blend_op = SDL_GPU_BLENDOP_ADD;
    colorTargetBlendState.src_alpha_blendfactor = SDL_GPU_BLENDFACTOR_SRC_ALPHA;
    colorTargetBlendState.dst_alpha_blendfactor = SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA;
    colorTargetBlendState.alpha_blend_op = SDL_GPU_BLENDOP_ADD;
    colorTargetBlendState.color_write_mask =
        SDL_GPU_COLORCOMPONENT_R | SDL_GPU_COLORCOMPONENT_G | SDL_GPU_COLORCOMPONENT_B |
        SDL_GPU_COLORCOMPONENT_A;
    colorTargetBlendState.enable_blend = true;

    SDL_GPUColorTargetDescription colorTargetDescription{};
    colorTargetDescription.format =
        SDL_GetGPUSwapchainTextureFormat(device_.get(), window_.get());
    colorTargetDescription.blend_state = colorTargetBlendState;

    SDL_GPUGraphicsPipelineTargetInfo targetInfo{};
    targetInfo.color_target_descriptions = &colorTargetDescription;
    targetInfo.num_color_targets = 1;

    graphicsPipeline_ = ejff::gpu::GraphicsPipeline(
        device_, vertexShader, fragmentShader, vertexInputState,
        SDL_GPU_PRIMITIVETYPE_TRIANGLELIST, rasterizerState, multisampleState,
        depthStencilState, targetInfo);

    vertexBuffer_ = gpu::Buffer(device_, gpu::Buffer::UsageFlags::eVertex,
                                sizeof(gpu::Vertex) * vertices.size());

    indexBuffer_ = gpu::Buffer(device_, gpu::Buffer::UsageFlags::eIndex,
                               sizeof(Uint32) * indices.size());

    gpu::TransferBuffer transferBuffer(device_, SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD,
                                       sizeof(gpu::Vertex) * vertices.size() +
                                           sizeof(Uint32) * indices.size());

    transferBuffer.upload(device_, vertices.data(), sizeof(gpu::Vertex) * vertices.size(),
                          0);
    transferBuffer.upload(device_, indices.data(), sizeof(uint32_t) * indices.size(),
                          sizeof(gpu::Vertex) * vertices.size());

    gpu::CommandBuffer commandBuffer(device_);
    gpu::CopyPass copyPass(commandBuffer);

    copyPass.uploadToBuffer(transferBuffer, 0, vertexBuffer_, 0,
                            sizeof(gpu::Vertex) * vertices.size());
    copyPass.uploadToBuffer(transferBuffer, sizeof(gpu::Vertex) * vertices.size(),
                            indexBuffer_, 0, sizeof(Uint32) * indices.size());

    sampler_ = gpu::Sampler(device_, SDL_GPU_FILTER_LINEAR, SDL_GPU_FILTER_LINEAR,
                            SDL_GPU_SAMPLERMIPMAPMODE_LINEAR,
                            SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE,
                            SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE,
                            SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE, 0.0f, 0.0f,
                            SDL_GPU_COMPAREOP_ALWAYS, 0.0f, 0.0f, false, false);

    auto imageSurface = Surface("../assets/textures/003_basecolor_0.png");
    imageSurface.convert(SDL_PIXELFORMAT_ABGR8888);
    imageSurface.flip(SDL_FLIP_VERTICAL);

    texture_ = gpu::Texture(device_, SDL_GPU_TEXTURETYPE_2D,
                            SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM,
                            SDL_GPU_TEXTUREUSAGE_SAMPLER, imageSurface.get()->w,
                            imageSurface.get()->h, 1, 1, SDL_GPU_SAMPLECOUNT_1);

    gpu::TransferBuffer textureTransferBuffer(device_, SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD,
                                              imageSurface.get()->h *
                                                  imageSurface.get()->pitch);

    textureTransferBuffer.upload(device_, imageSurface.get()->pixels,
                                 imageSurface.get()->h * imageSurface.get()->pitch);

    copyPass.uploadToTexture(textureTransferBuffer, 0, imageSurface.get()->w,
                             imageSurface.get()->h, texture_, 0, 0, 0, 0, 0,
                             imageSurface.get()->w, imageSurface.get()->h, 1);
}

Application::~Application()
{
    if (device_)
    {
        if (window_)
        {
            SDL_ReleaseWindowFromGPUDevice(device_.get(), window_.get());
        }
    }
}

void Application::iterate()
{
    gpu::CommandBuffer commandBuffer(device_);

    SDL_GPUTexture *swapchainTexture;
    if (!SDL_WaitAndAcquireGPUSwapchainTexture(commandBuffer.get(), window_.get(),
                                               &swapchainTexture, nullptr, nullptr))
    {
        throw std::runtime_error(
            fmt::format("Couldn't acquire SDL_GPUTexture. "
                        "SDL_WaitAndAcquireGPUSwapchainTexture failed: {}",
                        SDL_GetError()));
    }

    if (swapchainTexture)
    {
        SDL_GPUColorTargetInfo colorTargetInfo{};
        colorTargetInfo.texture = swapchainTexture;
        colorTargetInfo.clear_color = {0.0f, 0.0f, 0.0f, 1.0f};
        colorTargetInfo.load_op = SDL_GPU_LOADOP_CLEAR;
        colorTargetInfo.store_op = SDL_GPU_STOREOP_STORE;

        gpu::RenderPass renderPass(commandBuffer, &colorTargetInfo, 1, nullptr);

        graphicsPipeline_.bind(renderPass);

        SDL_GPUBufferBinding vertexBufferBinding{};
        vertexBufferBinding.buffer = vertexBuffer_.get();
        vertexBufferBinding.offset = 0;

        SDL_BindGPUVertexBuffers(renderPass.get(), 0, &vertexBufferBinding, 1);

        SDL_GPUBufferBinding indexBufferBinding{};
        indexBufferBinding.buffer = indexBuffer_.get();
        indexBufferBinding.offset = 0;

        SDL_BindGPUIndexBuffer(renderPass.get(), &indexBufferBinding,
                               SDL_GPU_INDEXELEMENTSIZE_32BIT);

        SDL_GPUTextureSamplerBinding textureSamplerBinding{};
        textureSamplerBinding.texture = texture_.get();
        textureSamplerBinding.sampler = sampler_.get();

        SDL_BindGPUFragmentSamplers(renderPass.get(), 0, &textureSamplerBinding, 1);

        SDL_DrawGPUIndexedPrimitives(renderPass.get(),
                                     static_cast<Uint32>(indices.size()), 1, 0, 0, 0);
    }
}

SDL_AppResult Application::event(const SDL_Event &event)
{
    switch (event.type)
    {
    case SDL_EVENT_QUIT:
    case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
        return SDL_APP_SUCCESS;

    case SDL_EVENT_KEY_DOWN:
        switch (event.key.scancode)
        {
        case SDL_SCANCODE_ESCAPE:
            return SDL_APP_SUCCESS;

        default:
            break;
        }

    default:
        break;
    }

    return SDL_APP_CONTINUE;
}

} // namespace ejff