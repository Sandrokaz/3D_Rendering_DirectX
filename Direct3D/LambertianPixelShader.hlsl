Texture2D mainTex : register(t0);
sampler mainSampler : register(s0);

cbuffer LightBuffer : register (b0) // has to be aligned in 16 byte blocks
{
  

    float3 lightDirection;
    float lightIntensity;
    float4 lightColor;

    float4 ambientColor;
    float ambientLightPower;

    float4 diffuseColor;

    float4 specularColor;
    float specularPower;

    float glosiness;
};


struct PixelInput
{
    float4 position : POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
};

float4 main(PixelInput INPUT) : SV_TARGET
{
    //Lambertian diffuse
    float3 normal = normalize(INPUT.normal);
    float4 color = mainTex.Sample(mainSampler, INPUT.uv);

    float3 pointToLight = normalize(lightDirection - INPUT.position);

    //Lout = L * NCLi
    //L = vector, pointing from surface to light source
    //N = surface normal
    //C = color
    //Li = LightIntensity
    float4 Lout = dot(pointToLight, normal) * color * lightIntensity;
    return Lout;

}