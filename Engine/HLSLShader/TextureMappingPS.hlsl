struct VSOutput
{
    float4 position : SV_Position;
    float2 texCoord : TEXCOORD;
    float3 normal : NORMAL;
};

Texture2D diffuseMap : register(t0);
SamplerState diffuseSampler : register(s0);

float4 main(VSOutput input) : SV_TARGET
{
    float4 diffuseColor = diffuseMap.Sample(diffuseSampler, input.texCoord);
    
    float3 lightDir = normalize(float3(500.0f, 500.0f, -500.f)); // hard-coded & normalized light direction
    
    float NdotL = dot(normalize(input.normal), lightDir); // Lambert's cosine law
    
    // return diffuseColor * NdotL;
    return float4(NdotL, NdotL, NdotL, 1);
}