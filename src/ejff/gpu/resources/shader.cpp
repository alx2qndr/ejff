#include "ejff/gpu/resources/shader.hpp"
#include "ejff/gpu/device.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include <fmt/format.h>

namespace ejff::gpu
{

Shader::Shader(Device &device, const std::filesystem::path &path, uint32_t numSamplers,
               uint32_t numStorageTextures, uint32_t numStorageBuffers,
               uint32_t numUniformBuffers)
    : ptr_(create(device, path, numSamplers, numStorageTextures, numStorageBuffers,
                  numUniformBuffers),
           SDL_GPUShaderDeleter{device.get()})
{
}

SDL_GPUShader *Shader::create(Device &device, const std::filesystem::path &path,
                              uint32_t numSamplers, uint32_t numStorageTextures,
                              uint32_t numStorageBuffers, uint32_t numUniformBuffers)
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
        throw std::runtime_error(
            fmt::format("Invalid shader extension '{}'.", extension));
    }

    SDL_GPUShaderFormat backendFormats = SDL_GetGPUShaderFormats(device.get());
    SDL_GPUShaderFormat format = SDL_GPU_SHADERFORMAT_INVALID;
    std::string formatFolder;
    std::string formatExt;
    std::string entrypoint;

    if (backendFormats & SDL_GPU_SHADERFORMAT_SPIRV)
    {
        format = SDL_GPU_SHADERFORMAT_SPIRV;
        formatFolder = "spv";
        formatExt = "spv";
        entrypoint = "main";
    }
    else if (backendFormats & SDL_GPU_SHADERFORMAT_MSL)
    {
        format = SDL_GPU_SHADERFORMAT_MSL;
        formatFolder = "msl";
        formatExt = "metal";
        entrypoint = "main0";
    }
    else if (backendFormats & SDL_GPU_SHADERFORMAT_DXIL)
    {
        format = SDL_GPU_SHADERFORMAT_DXIL;
        formatFolder = "dxil";
        formatExt = "dxil";
        entrypoint = "main";
    }
    else
    {
        throw std::runtime_error("Unrecognized backend shader format.");
    }

    auto filename = path.filename();
    std::filesystem::path binary_path =
        path.parent_path().parent_path() / "bin" / formatFolder;
    binary_path /= filename;
    binary_path += "." + formatExt;

    binary_path = std::filesystem::absolute(binary_path).lexically_normal();

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

    SDL_GPUShaderCreateInfo createInfo{};
    createInfo.code_size = static_cast<size_t>(buffer.size());
    createInfo.code = reinterpret_cast<Uint8 *>(buffer.data());
    createInfo.entrypoint = entrypoint.c_str();
    createInfo.format = format;
    createInfo.stage = stage;
    createInfo.num_samplers = static_cast<Uint32>(numSamplers);
    createInfo.num_storage_textures = static_cast<Uint32>(numStorageTextures);
    createInfo.num_storage_buffers = static_cast<Uint32>(numStorageBuffers);
    createInfo.num_uniform_buffers = static_cast<Uint32>(numUniformBuffers);

    auto shader = SDL_CreateGPUShader(device.get(), &createInfo);
    if (!shader)
    {
        throw std::runtime_error(
            fmt::format("Couldn't create SDL_GPUShader. SDL_CreateGPUShader failed: {}",
                        SDL_GetError()));
    }

    return shader;
}

} // namespace ejff::gpu