struct VSInput
{
    float3 position : POSITION;
    float2 texCoord : TEXCOORD;
};

cbuffer Transform : register(b0)
{
    matrix worldMatrix;
};

struct VSOutput
{
    float4 position : SV_Position;
    float2 texCoord : TEXCOORD;
};

VSOutput main(VSInput input)
{
    VSOutput output;
    output.position = mul(float4(input.position, 1), worldMatrix);
    output.texCoord = input.texCoord;
    
    return output;
}