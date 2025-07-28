#include "ejff/application.hpp"

#include "ejff/gpu/resources/command_buffer.hpp"
#include "ejff/gpu/resources/copy_pass.hpp"
#include "ejff/gpu/resources/render_pass.hpp"
#include "ejff/gpu/resources/shader.hpp"
#include "ejff/gpu/resources/transfer_buffer.hpp"
#include "ejff/gpu/resources/vertex.hpp"
#include "ejff/surface.hpp"

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

Application::Application()
{
    window_ = Window("Hello, Unnamed Window!", 640, 480,
                     SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);

    device_ = gpu::Device(SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_MSL |
                              SDL_GPU_SHADERFORMAT_DXIL,
                          true, nullptr);

    if (!SDL_ClaimWindowForGPUDevice(device_.get(), window_.get()))
    {
        throw std::runtime_error(
            fmt::format("Couldn't claim SDL_GPUWindow for SDL_GPUDevice. "
                        "SDL_ClaimWindowForGPUDevice failed: {}",
                        SDL_GetError()));
    }

    auto vertex_shader = gpu::Shader(device_, "../shaders/src/triangle.vert", 0, 0, 0, 0);
    auto fragment_shader =
        gpu::Shader(device_, "../shaders/src/triangle.frag", 1, 0, 0, 0);

    graphics_pipeline_ = ejff::gpu::GraphicsPipeline::create_default_pipeline(
        device_, vertex_shader, fragment_shader, window_);

    vertex_buffer_ = gpu::Buffer(device_, SDL_GPU_BUFFERUSAGE_VERTEX,
                                 sizeof(gpu::Vertex) * vertices.size());

    index_buffer_ =
        gpu::Buffer(device_, SDL_GPU_BUFFERUSAGE_INDEX, sizeof(Uint32) * indices.size());

    gpu::TransferBuffer transfer_buffer(device_, SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD,
                                        sizeof(gpu::Vertex) * vertices.size() +
                                            sizeof(Uint32) * indices.size());

    transfer_buffer.upload(device_, vertices.data(),
                           sizeof(gpu::Vertex) * vertices.size(), 0);
    transfer_buffer.upload(device_, indices.data(), sizeof(uint32_t) * indices.size(),
                           sizeof(gpu::Vertex) * vertices.size());

    gpu::CommandBuffer command_buffer(device_);
    gpu::CopyPass copy_pass(command_buffer);

    SDL_GPUTransferBufferLocation vertex_transfer_buffer_source{};
    vertex_transfer_buffer_source.transfer_buffer = transfer_buffer.get();
    vertex_transfer_buffer_source.offset = 0;

    SDL_GPUBufferRegion vertex_buffer_destination{};
    vertex_buffer_destination.buffer = vertex_buffer_.get();
    vertex_buffer_destination.offset = 0;
    vertex_buffer_destination.size = sizeof(gpu::Vertex) * vertices.size();

    copy_pass.upload_to_buffer(vertex_transfer_buffer_source, vertex_buffer_destination,
                               false);

    SDL_GPUTransferBufferLocation index_transfer_buffer_source{};
    index_transfer_buffer_source.transfer_buffer = transfer_buffer.get();
    index_transfer_buffer_source.offset = sizeof(gpu::Vertex) * vertices.size();

    SDL_GPUBufferRegion index_buffer_destination{};
    index_buffer_destination.buffer = index_buffer_.get();
    index_buffer_destination.offset = 0;
    index_buffer_destination.size = sizeof(Uint32) * indices.size();

    copy_pass.upload_to_buffer(index_transfer_buffer_source, index_buffer_destination,
                               false);

    sampler_ = gpu::Sampler(device_, SDL_GPU_FILTER_LINEAR, SDL_GPU_FILTER_LINEAR,
                            SDL_GPU_SAMPLERMIPMAPMODE_LINEAR,
                            SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE,
                            SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE,
                            SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE, 0.0f, 0.0f,
                            SDL_GPU_COMPAREOP_ALWAYS, 0.0f, 0.0f, false, false);

    auto image_surface = Surface::load_image("../assets/textures/003_basecolor_0.png");
    image_surface.convert(SDL_PIXELFORMAT_ABGR8888);
    image_surface.flip(SDL_FLIP_VERTICAL);

    texture_ = gpu::Texture(device_, SDL_GPU_TEXTURETYPE_2D,
                            SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM,
                            SDL_GPU_TEXTUREUSAGE_SAMPLER, image_surface.get()->w,
                            image_surface.get()->h, 1, 1, SDL_GPU_SAMPLECOUNT_1);

    gpu::TransferBuffer texture_transfer_buffer(
        device_, SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD,
        image_surface.get()->h * image_surface.get()->pitch);

    texture_transfer_buffer.upload(device_, image_surface.get()->pixels,
                                   image_surface.get()->h * image_surface.get()->pitch);

    SDL_GPUTextureTransferInfo texture_transfer_source{};
    texture_transfer_source.transfer_buffer = texture_transfer_buffer.get();
    texture_transfer_source.offset = 0;

    SDL_GPUTextureRegion texture_transfer_destination{};
    texture_transfer_destination.texture = texture_.get();
    texture_transfer_destination.w = image_surface.get()->w;
    texture_transfer_destination.h = image_surface.get()->h;
    texture_transfer_destination.d = 1;

    copy_pass.upload_to_texture(texture_transfer_source, texture_transfer_destination,
                                false);
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
    gpu::CommandBuffer command_buffer(device_);

    SDL_GPUTexture *swapchain_texture;
    if (!SDL_WaitAndAcquireGPUSwapchainTexture(command_buffer.get(), window_.get(),
                                               &swapchain_texture, nullptr, nullptr))
    {
        throw std::runtime_error(
            fmt::format("Couldn't acquire SDL_GPUTexture. "
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

        gpu::RenderPass render_pass(command_buffer, &color_target_info, 1, nullptr);

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

        SDL_GPUTextureSamplerBinding texture_sampler_binding{};
        texture_sampler_binding.texture = texture_.get();
        texture_sampler_binding.sampler = sampler_.get();

        SDL_BindGPUFragmentSamplers(render_pass.get(), 0, &texture_sampler_binding, 1);

        SDL_DrawGPUIndexedPrimitives(render_pass.get(),
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