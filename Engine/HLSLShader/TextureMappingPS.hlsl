struct VSOutput
{
    float4 position : SV_Position;
    float2 texCoord : TEXCOORD;
    float3 normal : NORMAL;
    float3 cameraPosition : TEXCOORD1;
    float3 worldPosition : TEXCOORD2;
};

cbuffer Light : register(b0)
{
    float3 lightPosition;
    float lightIntensity;
    float3 lightColor;
    float padding;
};

Texture2D map : register(t0);
SamplerState mapSampler : register(s0);

float4 main(VSOutput input) : SV_TARGET
{
    float4 diffuseMapColor = map.Sample(mapSampler, input.texCoord);
    
    // float3 lightDir = normalize(float3(500.0f, 500.0f, -500.f)); // hard-coded & normalized light direction
    float3 lightDir = normalize(input.worldPosition - lightPosition); // vertex to light vector; need to turn around
    
    float3 worldNormal = normalize(input.normal);
    
    float NdotL = dot(worldNormal, -lightDir); // Lambert's cosine law; turn lightDir 
    
    float specular = 0.0f;
    // Vanilla Phong shader
    //if (NdotL > 0) 
    //{
    //    // RdotV: dot product with Reflection Vector and View Direction Vector
    //    float3 reflection = reflect(lightDir, worldNormal);
    //    float3 viewDir = normalize(input.worldPosition - input.cameraPosition);
    
    //    // Flip the viewDir vector direction to compute the dot product with the reflection vector
    //    float RdotV = saturate(dot(reflection, -viewDir)); // == max(0, dot(reflection, -viewDir));
    //    float shineness = 16;
    //    specular = pow(RdotV, shineness);
    //}
    
    // Blinn Phong shader
    if (NdotL > 0)
    {
        float3 viewDir = normalize(input.worldPosition - input.cameraPosition);
        float3 halfVector = normalize(-lightDir + -viewDir);
    
        float NdotH = saturate(dot(halfVector, worldNormal));
        float shineness = 16;
        specular = pow(NdotH, shineness);
    }
        
    float4 finalColor = float4(0, 0, 0, 1);
    
    NdotL = pow(NdotL * 0.5f + 0.5f, 2); // Half-Lambert
    float4 diffuse = diffuseMapColor * NdotL;
    float4 specularColor = specular * float4(lightColor, 1);
    
    finalColor = diffuse + specularColor;
    
    // return diffuseColor * NdotL;
    return finalColor;
}