struct VSInput
{
    float3 position : POSITION;
    float2 texCoord : TEXCOORD;
};

cbuffer Transform : register(b0) // local to world
{
    matrix worldMatrix;
};

cbuffer Camera : register(b1) // world to view, view to projection
{
    matrix cameraMatrix;
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
    output.position = mul(output.position, cameraMatrix);
    output.texCoord = input.texCoord;
    
    return output;
}