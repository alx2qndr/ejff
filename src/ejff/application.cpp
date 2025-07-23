#include "ejff/application.hpp"

#include "ejff/gpu/resources/command_buffer.hpp"
#include "ejff/gpu/resources/copy_pass.hpp"
#include "ejff/gpu/resources/render_pass.hpp"
#include "ejff/gpu/resources/shader.hpp"
#include "ejff/gpu/resources/transfer_buffer.hpp"
#include "ejff/gpu/resources/vertex.hpp"

#include <vector>

#include <fmt/format.h>

namespace ejff
{

std::vector<gpu::resources::Vertex> vertices = {
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

Application::Application()
{
    window_ = Window("Hello, Unnamed Window!", 640, 480,
                     SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);

    device_ = gpu::Device(SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_MSL |
                              SDL_GPU_SHADERFORMAT_DXIL,
                          true, nullptr);

    if (!SDL_ClaimWindowForGPUDevice(device_.get(), window_.get()))
    {
        throw std::runtime_error(fmt::format("Couldn't claim SDL_GPUWindow for SDL_GPUDevice. "
                                             "SDL_ClaimWindowForGPUDevice failed: {}",
                                             SDL_GetError()));
    }
    auto vertex_shader =
        gpu::resources::Shader(device_, "../shaders/src/triangle.vert", 0, 0, 0, 0);
    auto fragment_shader =
        gpu::resources::Shader(device_, "../shaders/src/triangle.frag", 0, 0, 0, 0);

    graphics_pipeline_ = ejff::gpu::resources::GraphicsPipeline::create_default_pipeline(
        device_, vertex_shader, fragment_shader, window_);

    vertex_buffer_ = gpu::resources::Buffer(device_, SDL_GPU_BUFFERUSAGE_VERTEX,
                                            sizeof(gpu::resources::Vertex) * vertices.size());

    index_buffer_ =
        gpu::resources::Buffer(device_, SDL_GPU_BUFFERUSAGE_INDEX, sizeof(Uint32) * indices.size());

    gpu::resources::TransferBuffer transfer_buffer(
        device_, SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD,
        sizeof(gpu::resources::Vertex) * vertices.size() + sizeof(Uint32) * indices.size());

    const auto mapped_data = SDL_MapGPUTransferBuffer(device_.get(), transfer_buffer.get(), false);

    std::memcpy(mapped_data, vertices.data(), sizeof(gpu::resources::Vertex) * vertices.size());
    std::memcpy(static_cast<Uint8 *>(mapped_data) +
                    sizeof(gpu::resources::Vertex) * vertices.size(),
                indices.data(), sizeof(uint32_t) * indices.size());
    SDL_UnmapGPUTransferBuffer(device_.get(), transfer_buffer.get());

    gpu::resources::CommandBuffer command_buffer(device_);
    gpu::resources::CopyPass copy_pass(command_buffer);

    SDL_GPUTransferBufferLocation vertex_transfer_buffer_location{};
    vertex_transfer_buffer_location.transfer_buffer = transfer_buffer.get();
    vertex_transfer_buffer_location.offset = 0;

    SDL_GPUBufferRegion vertex_buffer_region{};
    vertex_buffer_region.buffer = vertex_buffer_.get();
    vertex_buffer_region.offset = 0;
    vertex_buffer_region.size = sizeof(gpu::resources::Vertex) * vertices.size();

    SDL_UploadToGPUBuffer(copy_pass.get(), &vertex_transfer_buffer_location, &vertex_buffer_region,
                          false);

    SDL_GPUTransferBufferLocation index_transfer_buffer_location{};
    index_transfer_buffer_location.transfer_buffer = transfer_buffer.get();
    index_transfer_buffer_location.offset = sizeof(gpu::resources::Vertex) * vertices.size();

    SDL_GPUBufferRegion index_buffer_region{};
    index_buffer_region.buffer = index_buffer_.get();
    index_buffer_region.offset = 0;
    index_buffer_region.size = sizeof(Uint32) * indices.size();

    SDL_UploadToGPUBuffer(copy_pass.get(), &index_transfer_buffer_location, &index_buffer_region, false);
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
    gpu::resources::CommandBuffer command_buffer(device_);

    SDL_GPUTexture *swapchain_texture;
    if (!SDL_WaitAndAcquireGPUSwapchainTexture(command_buffer.get(), window_.get(),
                                               &swapchain_texture, nullptr, nullptr))
    {
        throw std::runtime_error(fmt::format("Couldn't acquire SDL_GPUTexture. "
                                             "SDL_WaitAndAcquireGPUSwapchainTexture failed: {}",
                                             SDL_GetError()));
    }

    if (swapchain_texture)
    {
        SDL_GPUColorTargetInfo color_target_info{};
        color_target_info.texture = swapchain_texture;
        color_target_info.clear_color = {0.0f, 0.0f, 0.0f, 1.0f};
        color_target_info.load_op = SDL_GPU_LOADOP_CLEAR;
        color_target_info.store_op = SDL_GPU_STOREOP_STORE;

        gpu::resources::RenderPass render_pass(command_buffer, &color_target_info, 1, nullptr);

        graphics_pipeline_.bind(render_pass);

        SDL_GPUBufferBinding vertex_buffer_binding{};
        vertex_buffer_binding.buffer = vertex_buffer_.get();
        vertex_buffer_binding.offset = 0;

        SDL_BindGPUVertexBuffers(render_pass.get(), 0, &vertex_buffer_binding, 1);

        SDL_GPUBufferBinding index_buffer_binding{};
        index_buffer_binding.buffer = index_buffer_.get();
        index_buffer_binding.offset = 0;

        SDL_BindGPUIndexBuffer(render_pass.get(), &index_buffer_binding,
                               SDL_GPU_INDEXELEMENTSIZE_32BIT);
        SDL_DrawGPUIndexedPrimitives(render_pass.get(), static_cast<Uint32>(indices.size()), 1, 0,
                                     0, 0);
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