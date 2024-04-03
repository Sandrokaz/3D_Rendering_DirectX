Texture2D mainTex : register(t0);
sampler mainSampler : register(s0);

cbuffer LightBuffer : register (b0) 
{
  
    float4 ambientColor;
    float4 diffuseColor;
    float specularPower;
    float4 specularColor;
    float3 lightDirection;
    float lightIntensity;
    float4 lightColor;
    float ambientLightPower;
    float glosiness;
    float padding;
};


struct PixelInput
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
};

float4 main(PixelInput IN) : SV_TARGET
{
    float4 textureColor;
    float3 lightDir;
    float lightIntensity;
    float4 color;
    float3 reflection;
    float4 specular;
    
    
    
    
    
    //Lambertian diffuse
    float3 normal = normalize(IN.normal);
    textureColor = mainTex.Sample(mainSampler, IN.uv);

    
    lightDir = lightDirection;
    lightIntensity = saturate(dot(lightDir, IN.normal));
    
    
    
    float3 pointToLight = normalize(lightDirection - IN.position.xyz);

    //Lout = L * NCLi
    //L = vector, pointing from surface to light source
    //N = surface normal
    //C = color
    //Li = LightIntensity
    float4 Lout = dot(pointToLight, normal) * textureColor * lightIntensity;
    return Lout;

}