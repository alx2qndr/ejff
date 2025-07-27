struct Input
{
    float3 position : TEXCOORD0;
    float4 color : TEXCOORD1;
    float2 uv : TEXCOORD2;
    float3 normal : TEXCOORD3;
};

struct Output
{
    float4 color : TEXCOORD0;
    float4 position : SV_Position;
    float2 uv : TEXCOORD1;
    float3 normal : TEXCOORD2;
};

Output main(Input input)
{
    Output output;
    output.color = input.color;
    output.position = float4(input.position, 1.0f);
    output.uv = input.uv;
    output.normal = input.normal;
    return output;
}
