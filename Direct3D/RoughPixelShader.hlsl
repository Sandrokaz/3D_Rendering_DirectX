//Texture2D mainTex :  register (t0);
//Texture2D normalMap : register(t1)
//sampler mainSampler;
//
//cbuffer LightBuffer : register(b0)
//{
//    float4 ambientColor;
//    float4 diffuseColor;
//    float3 lightDirection;
//    float specularPower;
//    float4 specularColor;
//    float roughness;
//    float3 padding;
//};
//
//struct PixelInput
//{
//    float4 position : SV_POSITION;
//    float2 uv : TEXCOORD0;
//    float3 normal : NORMAL;
//    float3 viewDirection : TEXCOORD1;
//};
//
//float4 main(PixelInput input) : SV_TARGET
//{
//        // Sample the texture
//    float4 texColor = mainTex.Sample(mainSampler, input.uv);
//    float4 color = ambientColor;
//    
//    float3 normal = input.normal;
//    normal = normalize(input.normal);
//    
//    // we have to change normal of everypixel not for vertexshader
//    // 
//
//   
//
//    return color;
//
//}

Texture2D mainTex : register(t0);
Texture2D normalMap : register(t1);
sampler mainSampler;

cbuffer LightBuffer : register(b0)
{
    float4 ambientColor;
    float4 diffuseColor;
    float3 lightDirection;
    float specularPower;
    float4 specularColor;
    float roughness;
    float3 padding;
};

struct PixelInput
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD0;
    float3 normal : NORMAL;
};

float3 CalculateTangentSpaceVector(float3 worldNormal, float3 worldTangent, float3 worldBitangent, float2 texCoord)
{
    float3 normalMap = normalMap.Sample(mainSampler, texCoord).xyz * 2.0 - 1.0;

    float3 tangentNormal = normalize(mul(normalMap, float3x3(worldTangent, worldBitangent, worldNormal)));
    return tangentNormal;
}

float3 CalculateDiffuseLight(float3 normal, float3 lightDirection, float3 diffuseColor)
{
    float diffuse = max(dot(normal, lightDirection), 0.0f);
    return diffuseColor * diffuse;
}

float3 CalculateSpecularLight(float3 viewDirection, float3 normal, float3 lightDirection, float4 specularColor, float specularPower, float roughness)
{
    float3 reflection = reflect(-lightDirection, normal);
    float specular = pow(saturate(dot(reflection, viewDirection)), specularPower);
    return specularColor.xyz * specular * (1 - roughness);
}

float3 CalculateAmbientLight(float3 ambientColor)
{
    return ambientColor;
}

float4 main(PixelInput input) : SV_TARGET
{
    float3 worldNormal = normalize(input.normal);
    float3 worldTangent = normalize(cross(float3(0.0f, 1.0f, 0.0f), worldNormal));
    float3 worldBitangent = cross(worldNormal, worldTangent);

    float3 tangentSpaceNormal = CalculateTangentSpaceVector(worldNormal, worldTangent, worldBitangent, input.uv);

    float3 diffuse = CalculateDiffuseLight(tangentSpaceNormal, lightDirection, diffuseColor.xyz);
    float3 specular = CalculateSpecularLight(normalize(input.viewDirection), tangentSpaceNormal, lightDirection, specularColor, specularPower, roughness);
    float3 ambient = CalculateAmbientLight(ambientColor.xyz);

    return float4(diffuse + specular + ambient, 1.0f) * mainTex.Sample(mainSampler, input.uv);
}
