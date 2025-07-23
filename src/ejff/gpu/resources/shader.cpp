#include "ejff/gpu/resources/shader.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include <fmt/format.h>

namespace ejff::gpu::resources
{

Shader::Shader(Device &device, const std::filesystem::path &path, Uint32 num_samplers,
               Uint32 num_storage_textures, Uint32 num_storage_buffers, Uint32 num_uniform_buffers)
    : ptr_(nullptr, SDL_GPUShaderDeleter{device.get()})
{
    auto const extension = path.extension().string();

    SDL_GPUShaderStage stage;
    if (extension == ".vert")
    {
        stage = SDL_GPU_SHADERSTAGE_VERTEX;
    }
    else if (extension == ".frag")
    {
        stage = SDL_GPU_SHADERSTAGE_FRAGMENT;
    }
    else
    {
        throw std::runtime_error(fmt::format("Invalid shader extension '{}'.", extension));
    }

    SDL_GPUShaderFormat backend_formats = SDL_GetGPUShaderFormats(device.get());
    SDL_GPUShaderFormat format = SDL_GPU_SHADERFORMAT_INVALID;
    std::string format_folder;
    std::string format_ext;
    std::string entrypoint;

    if (backend_formats & SDL_GPU_SHADERFORMAT_SPIRV)
    {
        format = SDL_GPU_SHADERFORMAT_SPIRV;
        format_folder = "spv";
        format_ext = "spv";
        entrypoint = "main";
    }
    else if (backend_formats & SDL_GPU_SHADERFORMAT_MSL)
    {
        format = SDL_GPU_SHADERFORMAT_MSL;
        format_folder = "msl";
        format_ext = "metal";
        entrypoint = "main0";
    }
    else if (backend_formats & SDL_GPU_SHADERFORMAT_DXIL)
    {
        format = SDL_GPU_SHADERFORMAT_DXIL;
        format_folder = "dxil";
        format_ext = "dxil";
        entrypoint = "main";
    }
    else
    {
        throw std::runtime_error("Unrecognized backend shader format.");
    }

    auto filename = path.filename();
    std::filesystem::path binary_path = path.parent_path().parent_path() / "bin" / format_folder;
    binary_path /= filename;
    binary_path += "." + format_ext;

    std::ifstream file(binary_path, std::ios::binary | std::ios::ate);
    if (!file)
    {
        throw std::runtime_error(
            fmt::format("Couldn't open shader binary '{}'", binary_path.string()));
    }

    auto size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<std::byte> buffer(size);
    if (!file.read(reinterpret_cast<char *>(buffer.data()), size))
    {
        throw std::runtime_error(
            fmt::format("Couldn't read shader binary '{}'", binary_path.string()));
    }

    SDL_GPUShaderCreateInfo createinfo{};
    createinfo.code_size = buffer.size();
    createinfo.code = reinterpret_cast<Uint8 *>(buffer.data());
    createinfo.entrypoint = entrypoint.c_str();
    createinfo.format = format;
    createinfo.stage = stage;
    createinfo.num_samplers = num_samplers;
    createinfo.num_storage_textures = num_storage_textures;
    createinfo.num_storage_buffers = num_storage_buffers;
    createinfo.num_uniform_buffers = num_uniform_buffers;
    createinfo.props = {};

    auto shader = SDL_CreateGPUShader(device.get(), &createinfo);
    if (!shader)
    {
        throw std::runtime_error(fmt::format(
            "Couldn't create SDL_GPUShader. SDL_CreateGPUShader failed: {}", SDL_GetError()));
    }

    ptr_.reset(shader);
}

} // namespace ejff::gpu::resources