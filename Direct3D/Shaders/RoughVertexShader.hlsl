cbuffer matrixBuffer : register(b0)
{
    matrix worldViewProjectionMatrix;
    matrix worldMatrix;
  
};
cbuffer cameraBuffer : register(b1)
{
    float3 cameraPosition;
    float pad;
};

struct VertexInput
{
    float3 position : POSITION;
    float2 uv : TEXCOORD0;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float3 bitangent : BITANGENT;
    
};

struct VertexOutput
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD0;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float3 bitangent : BITANGENT;
    float3 viewDirection : TEXCOORD1;


};

VertexOutput main(VertexInput IN)
{

    VertexOutput OUT;

   
   
	OUT.position = mul(float4(IN.position, 1.0f), worldViewProjectionMatrix); // Multiply the vertex position by the world-view-projection matrix to get the final screen position

    OUT.normal = normalize(mul(IN.normal, (float3x3) worldMatrix));        
    OUT.uv = IN.uv; // Copy the texture coordinates to the output
    OUT.tangent = normalize( mul(IN.tangent.xyz, (float3x3) worldMatrix));
	OUT.bitangent = normalize(mul(cross(IN.normal, IN.tangent.xyz), (float3x3) worldMatrix));
    OUT.viewDirection = normalize(cameraPosition.xyz - mul(float4(IN.position, 1.0f), worldMatrix).xyz);
    
    
    
    return OUT;

}
