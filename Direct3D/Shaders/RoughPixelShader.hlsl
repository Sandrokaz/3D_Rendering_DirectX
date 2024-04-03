Texture2D mainTex : register(t0);
Texture2D normalMapTex : register(t1);
sampler mainSampler : register (s0);
sampler normalSampler : register (s1);

cbuffer LightBuffer : register(b0)
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
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD0;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float3 bitangent : BITANGENT;
    float3 viewDirection : TEXCOORD1;
};


float3 CalculateNormal(in PixelInput IN)
{
    float4 normalMap = normalMapTex.Sample(normalSampler, IN.uv);
    normalMap = normalMap * 2.0f - 1.0f;

    // calculate normal
    float3 normal = normalize(IN.normal);
    float3 tangent = normalize(IN.tangent);
    float3 bitangent = normalize(IN.bitangent);

    return normalize(
        tangent * normalMap.r +
        bitangent * normalMap.g +
        normal * normalMap.b
    );



}


float4 main(PixelInput IN) : SV_TARGET
{
 
         float4 textureColor = mainTex.Sample(normalSampler, IN.uv);
         float3 lightDir = normalize(-lightDirection);
         float3 normal = CalculateNormal(IN);
         float3 viewDir = normalize(IN.viewDirection);
         float3 reflectVector = reflect(-lightDir, normal);
         

	     float4 diffColor = 0;
         float diffuse = max(dot(normal, lightDir),0);
	       diffColor = lightColor * (diffuse * lightIntensity);


         float3 ambColor = ambientColor * ambientLightPower;
         
         float4 specColor = 0;
         float specular = pow(max(dot(reflectVector, viewDir), 0), specularPower * 128) * glosiness;
         specColor = specularColor * specular;
         
	    return saturate(textureColor * saturate(float4(ambColor, 1.0f) + diffColor) + specColor);
         
}
