struct VSInput
{
    float3 position : POSITION;
    float2 texCoord : TEXCOORD;
    float3 normal : NORMAL;
};

cbuffer Transform : register(b0) // local to world
{
    matrix worldMatrix;
};

cbuffer Camera : register(b1) // world to view, view to projection
{
    matrix cameraMatrix;
    float3 cameraPosition;
    float padding; // constant buffer must be aligned with 16bytes
};

struct VSOutput
{
    float4 position : SV_Position;
    float2 texCoord : TEXCOORD;
    float3 normal : NORMAL;
    float3 cameraPosition : TEXCOORD1;
    float3 worldPosition : TEXCOORD2;
};

VSOutput main(VSInput input)
{
    VSOutput output;
    output.position = mul(float4(input.position, 1), worldMatrix);
    output.worldPosition = output.position.xyz;
    
    output.position = mul(output.position, cameraMatrix);
    output.texCoord = input.texCoord;
    
    output.normal = normalize(mul(input.normal, (float3x3) worldMatrix)); // transform local normal to world normal
    
    output.cameraPosition = cameraPosition;
    
    return output;
}