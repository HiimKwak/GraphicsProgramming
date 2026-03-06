struct VSOutput
{
    float4 position : SV_Position;
    float2 texCoord : TEXCOORD;
};

Texture2D diffuseMap : register(t0);
SamplerState diffuseSampler : register(s0);

float4 main(VSOutput input) : SV_TARGET
{
    float4 diffuseColor = diffuseMap.Sample(diffuseSampler, input.texCoord);
    
    return diffuseColor;
}