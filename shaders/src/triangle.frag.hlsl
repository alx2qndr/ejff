Texture2D<float4> TextureMap : register(t0, space2);
SamplerState TextureSampler : register(s0, space2);

struct Output
{
    float4 color : TEXCOORD0;
    float4 position : SV_Position;
    float2 uv : TEXCOORD1;
    float3 normal : TEXCOORD2;
};

float4 main(Output input) : SV_Target
{
    float4 textureColor = TextureMap.Sample(TextureSampler, input.uv);
    return input.color * textureColor;
}
