Texture2D mainTex;
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
    float4 position : SV_Position;
    float2 uv : TEXCOORD0;
    float3 normal : NORMAL;
    float3 viewDirection : TEXCOORD1;
};

float4 main(PixelInput input) : SV_TARGET
{
    float4 textureColor;
    float3 lightDir;
    float lightIntensity;
    float4 color;
    float3 reflection;
    float4 specular;


    textureColor = mainTex.Sample(mainSampler, input.uv);   // Sample the texture color using the given sampler and texture
    color = ambientColor;     // Set the initial ambient color

    // Compute the normal vector and normalize it
    float3 normal = input.normal;
    normal = normalize(input.normal);

    // Set the initial specular color
    specular = specularColor;


    // Compute the diffuse lighting
    lightDir = lightDirection;
    lightIntensity = saturate(dot(lightDir, input.normal));

    if (lightIntensity > 0)
    {

        // Compute the diffuse color
        color += (diffuseColor * lightIntensity);
        color = saturate(color);

        // Compute the reflection vector and the specular color
        reflection = normalize(2 * lightIntensity * normal - lightDir);
        specular = pow(saturate(dot(reflection, input.viewDirection)), specularPower);
    }

    // Combine the lighting with the texture color
    color = color * textureColor;
    color = saturate(color + specular);

    color.a = 1;

   

       return color;
}