#pragma once

#include "ejff/gpu/device.hpp"
#include "ejff/gpu/resources/buffer.hpp"
#include "ejff/gpu/resources/graphics_pipeline.hpp"
#include "ejff/gpu/resources/sampler.hpp"
#include "ejff/gpu/resources/texture.hpp"
#include "ejff/window.hpp"

#include <SDL3/SDL.h>

namespace ejff
{

class Application
{
public:
    Application();

    Application(const Application &) = delete;
    Application &operator=(const Application &) = delete;

    Application(Application &&) noexcept = delete;
    Application &operator=(Application &&) noexcept = delete;

    ~Application();

    void iterate();
    SDL_AppResult event(const SDL_Event &event);

private:
    Window window_;
    gpu::Device device_;
    gpu::GraphicsPipeline graphics_pipeline_;
    gpu::Buffer vertex_buffer_;
    gpu::Buffer index_buffer_;
    gpu::Texture texture_;
    gpu::Sampler sampler_;
};

} // namespace ejff