#pragma once

#include "ejff/gpu/resources/texture.hpp"
#include "ejff/gpu/resources/vertex.hpp"
#include "ejff/utilities/enable_bit_mask_operators.hpp"

#include <memory>
#include <vector>

#include <SDL3/SDL.h>

namespace ejff::gpu
{

class Device;
class RenderPass;
class Shader;

struct SDL_GPUGraphicsPipelineDeleter
{
    SDL_GPUDevice *device;

    SDL_GPUGraphicsPipelineDeleter(SDL_GPUDevice *device = nullptr)
        : device(device)
    {
    }

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
    enum class PrimitiveType : uint64_t
    {
        eTriangleList = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST,
        eTriangleStrip = SDL_GPU_PRIMITIVETYPE_TRIANGLESTRIP,
        eLineList = SDL_GPU_PRIMITIVETYPE_LINELIST,
        eLineStrip = SDL_GPU_PRIMITIVETYPE_LINESTRIP,
        ePointList = SDL_GPU_PRIMITIVETYPE_POINTLIST,
    };

    enum class FillMode : uint64_t
    {
        eFill = SDL_GPU_FILLMODE_FILL,
        eLine = SDL_GPU_FILLMODE_LINE
    };

    enum class CullMode : uint64_t
    {
        SDL_GPU_CULLMODE_NONE,
        SDL_GPU_CULLMODE_FRONT,
        SDL_GPU_CULLMODE_BACK
    };

    enum class FrontFace : uint64_t
    {
        eCounterClockWise = SDL_GPU_FRONTFACE_COUNTER_CLOCKWISE,
        eClockWise = SDL_GPU_FRONTFACE_CLOCKWISE
    };

    struct RasterizerState
    {
        FillMode fillMode{};
        CullMode cullMode{};
        FrontFace frontFace{};
        float depthBiasConstantFactor = 0.0f;
        float depthBiasClamp = 0.0f;
        float depthBiasSlopeFactor = 0.0f;
        bool enableDepthBias = false;
        bool enableDepthClip = false;

        SDL_GPURasterizerState get() const
        {
            SDL_GPURasterizerState rasterizerState{};
            rasterizerState.fill_mode = static_cast<SDL_GPUFillMode>(fillMode);
            rasterizerState.cull_mode = static_cast<SDL_GPUCullMode>(cullMode);
            rasterizerState.front_face =
                static_cast<SDL_GPUFrontFace>(frontFace);
            rasterizerState.depth_bias_constant_factor =
                depthBiasConstantFactor;
            rasterizerState.depth_bias_clamp = depthBiasClamp;
            rasterizerState.depth_bias_slope_factor = depthBiasSlopeFactor;
            rasterizerState.enable_depth_bias = enableDepthBias;
            rasterizerState.enable_depth_clip = enableDepthClip;
            return rasterizerState;
        }
    };

    enum class SampleCount : uint64_t
    {
        e1 = SDL_GPU_SAMPLECOUNT_1,
        e2 = SDL_GPU_SAMPLECOUNT_2,
        e4 = SDL_GPU_SAMPLECOUNT_4,
        e8 = SDL_GPU_SAMPLECOUNT_8
    };

    struct MultisampleState
    {
        SampleCount sampleCount = SampleCount::e1;
        uint32_t sampleMask = 0;
        bool enableMask = false;

        const SDL_GPUMultisampleState get() const
        {
            SDL_GPUMultisampleState multisampleState{};
            multisampleState.sample_count =
                static_cast<SDL_GPUSampleCount>(sampleCount);
            multisampleState.sample_mask = static_cast<Uint32>(sampleMask);
            multisampleState.enable_mask = enableMask;
            return multisampleState;
        }
    };

    enum class CompareOp : uint64_t
    {
        eInvalid = SDL_GPU_COMPAREOP_INVALID,
        eNever = SDL_GPU_COMPAREOP_NEVER,
        eLess = SDL_GPU_COMPAREOP_LESS,
        eEqual = SDL_GPU_COMPAREOP_EQUAL,
        eLessOrEqual = SDL_GPU_COMPAREOP_LESS_OR_EQUAL,
        eGreater = SDL_GPU_COMPAREOP_GREATER,
        eNotEqual = SDL_GPU_COMPAREOP_NOT_EQUAL,
        eGreaterOrEqual = SDL_GPU_COMPAREOP_GREATER_OR_EQUAL,
        eAlways = SDL_GPU_COMPAREOP_ALWAYS
    };

    enum class StencilOp : uint64_t
    {
        eInvalid = SDL_GPU_STENCILOP_INVALID,
        eKeep = SDL_GPU_STENCILOP_KEEP,
        eZero = SDL_GPU_STENCILOP_ZERO,
        eReplace = SDL_GPU_STENCILOP_REPLACE,
        eIncrementAndClamp = SDL_GPU_STENCILOP_INCREMENT_AND_CLAMP,
        eDecrementAndClamp = SDL_GPU_STENCILOP_DECREMENT_AND_CLAMP,
        eInvert = SDL_GPU_STENCILOP_INVERT,
        eIncrementAndWrap = SDL_GPU_STENCILOP_INCREMENT_AND_WRAP,
        eDecrementAndWrap = SDL_GPU_STENCILOP_DECREMENT_AND_WRAP
    };

    struct StencilOpState
    {
        StencilOp failOp{};
        StencilOp passOp{};
        StencilOp depthFailOp{};
        CompareOp compareOp{};

        SDL_GPUStencilOpState get() const
        {
            SDL_GPUStencilOpState stencilOpState{};
            stencilOpState.fail_op = static_cast<SDL_GPUStencilOp>(failOp);
            stencilOpState.pass_op = static_cast<SDL_GPUStencilOp>(passOp);
            stencilOpState.depth_fail_op =
                static_cast<SDL_GPUStencilOp>(depthFailOp);
            stencilOpState.compare_op =
                static_cast<SDL_GPUCompareOp>(compareOp);
            return stencilOpState;
        }
    };

    struct DepthStencilState
    {
        CompareOp compareOp{};
        StencilOpState backStencilState{};
        StencilOpState frontStencilState{};
        uint8_t compareMask = 0;
        uint8_t writeMask = 0;
        bool enableDepthTest = false;
        bool enableDepthWrite = false;
        bool enableStencilTest = false;

        SDL_GPUDepthStencilState get() const
        {
            SDL_GPUDepthStencilState depthStencilState{};
            depthStencilState.compare_op =
                static_cast<SDL_GPUCompareOp>(compareOp);
            depthStencilState.back_stencil_state = backStencilState.get();
            depthStencilState.front_stencil_state = frontStencilState.get();
            return depthStencilState;
        }
    };

    enum class BlendFactor : uint64_t
    {
        eInvalid = SDL_GPU_BLENDFACTOR_INVALID,
        eZero = SDL_GPU_BLENDFACTOR_ZERO,
        eOne = SDL_GPU_BLENDFACTOR_ONE,
        eSrcColor = SDL_GPU_BLENDFACTOR_SRC_COLOR,
        eOneMinusSrcColor = SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_COLOR,
        eDstColor = SDL_GPU_BLENDFACTOR_DST_COLOR,
        eOneMinusDstColor = SDL_GPU_BLENDFACTOR_ONE_MINUS_DST_COLOR,
        eSrcAlpha = SDL_GPU_BLENDFACTOR_SRC_ALPHA,
        eOneMinusSrcAlpha = SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
        eDstAlpha = SDL_GPU_BLENDFACTOR_DST_ALPHA,
        eOneMinusDstAlpha = SDL_GPU_BLENDFACTOR_ONE_MINUS_DST_ALPHA,
        eConstantColor = SDL_GPU_BLENDFACTOR_CONSTANT_COLOR,
        eOneMinusConstantColor = SDL_GPU_BLENDFACTOR_ONE_MINUS_CONSTANT_COLOR,
        eSrcAlphaSaturate = SDL_GPU_BLENDFACTOR_SRC_ALPHA_SATURATE
    };

    enum class BlendOp : uint64_t
    {
        eInvalid = SDL_GPU_BLENDOP_INVALID,
        eAdd = SDL_GPU_BLENDOP_ADD,
        eSubtract = SDL_GPU_BLENDOP_SUBTRACT,
        eReverseSubtract = SDL_GPU_BLENDOP_REVERSE_SUBTRACT,
        eMin = SDL_GPU_BLENDOP_MIN,
        eMax = SDL_GPU_BLENDOP_MAX
    };

    enum class ColorComponentFlags : uint64_t
    {
        eR = SDL_GPU_COLORCOMPONENT_R,
        eG = SDL_GPU_COLORCOMPONENT_G,
        eB = SDL_GPU_COLORCOMPONENT_B,
        eA = SDL_GPU_COLORCOMPONENT_A
    };

    struct ColorTargetBlendState
    {
        BlendFactor srcColorBlendFactor{};
        BlendFactor dstColorBlendFactor{};
        BlendOp colorBlendOp{};
        BlendFactor srcAlphaBlendFactor{};
        BlendFactor dstAlphaBlendFactor{};
        BlendOp alphaBlendOp{};
        ColorComponentFlags colorWriteMask{};
        bool enableBlend = false;
        bool enableColorWriteMask = false;

        SDL_GPUColorTargetBlendState get() const
        {
            SDL_GPUColorTargetBlendState colorTargetBlendState{};
            colorTargetBlendState.src_color_blendfactor =
                static_cast<SDL_GPUBlendFactor>(srcColorBlendFactor);
            colorTargetBlendState.dst_color_blendfactor =
                static_cast<SDL_GPUBlendFactor>(dstColorBlendFactor);
            colorTargetBlendState.color_blend_op =
                static_cast<SDL_GPUBlendOp>(colorBlendOp);
            colorTargetBlendState.src_alpha_blendfactor =
                static_cast<SDL_GPUBlendFactor>(srcAlphaBlendFactor);
            colorTargetBlendState.dst_alpha_blendfactor =
                static_cast<SDL_GPUBlendFactor>(dstAlphaBlendFactor);
            colorTargetBlendState.alpha_blend_op =
                static_cast<SDL_GPUBlendOp>(alphaBlendOp);
            colorTargetBlendState.enable_blend = enableBlend;
            colorTargetBlendState.color_write_mask =
                static_cast<Uint64>(colorWriteMask);
            colorTargetBlendState.enable_color_write_mask =
                enableColorWriteMask;
            return colorTargetBlendState;
        }
    };

    struct ColorTargetDescription
    {
        Texture::Format format = Texture::Format::eInvalid;
        ColorTargetBlendState blendState{};

        SDL_GPUColorTargetDescription get() const
        {
            SDL_GPUColorTargetDescription сolorTargetDescription{};
            сolorTargetDescription.format =
                static_cast<SDL_GPUTextureFormat>(format);
            сolorTargetDescription.blend_state = blendState.get();
            return сolorTargetDescription;
        }
    };

    struct TargetInfo
    {
        const ColorTargetDescription *pColorTargetDescriptions = nullptr;
        uint32_t colorTargetCount = 0;
        Texture::Format depthStencilFormat = Texture::Format::eInvalid;
        bool hasDepthStencilTarget = false;

        SDL_GPUGraphicsPipelineTargetInfo get() const
        {
            SDL_GPUGraphicsPipelineTargetInfo targetInfo{};
            if (pColorTargetDescriptions)
            {
                static std::vector<SDL_GPUColorTargetDescription> colorDescs;
                colorDescs.clear();
                for (uint32_t i = 0; i < colorTargetCount; ++i)
                {
                    colorDescs.push_back(pColorTargetDescriptions[i].get());
                }
                targetInfo.color_target_descriptions = colorDescs.data();
            }
            targetInfo.num_color_targets = colorTargetCount;
            targetInfo.depth_stencil_format =
                static_cast<SDL_GPUTextureFormat>(depthStencilFormat);
            targetInfo.has_depth_stencil_target = hasDepthStencilTarget;
            return targetInfo;
        }
    };

    GraphicsPipeline() = default;

    explicit GraphicsPipeline(
        Device &device, Shader &vertexShader, Shader &fragmentShader,
        Vertex::InputState vertexInputState, PrimitiveType primitiveType,
        RasterizerState rasterizerState, MultisampleState multisampleState,
        DepthStencilState depthStencilState, TargetInfo targetInfo);

    GraphicsPipeline(const GraphicsPipeline &) = delete;
    GraphicsPipeline &operator=(const GraphicsPipeline &) = delete;

    GraphicsPipeline(GraphicsPipeline &&) noexcept = default;
    GraphicsPipeline &operator=(GraphicsPipeline &&) noexcept = default;

    ~GraphicsPipeline() = default;

    void bind(RenderPass &renderPass);

    SDL_GPUGraphicsPipeline *get() const noexcept { return ptr_.get(); }

private:
    SDL_GPUGraphicsPipeline *create(
        Device &device, Shader &vertexShader, Shader &fragmentShader,
        Vertex::InputState vertexInputState, PrimitiveType primitiveType,
        RasterizerState rasterizerState, MultisampleState multisampleState,
        DepthStencilState depthStencilState, TargetInfo targetInfo);

    std::unique_ptr<SDL_GPUGraphicsPipeline, SDL_GPUGraphicsPipelineDeleter>
        ptr_{nullptr};
};

} // namespace ejff::gpu

ENABLE_BITMASK_OPERATORS(ejff::gpu::GraphicsPipeline::ColorComponentFlags);
