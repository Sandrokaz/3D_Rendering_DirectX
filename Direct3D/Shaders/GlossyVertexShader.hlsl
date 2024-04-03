// Define a constant buffer for matrices used to transform vertices
cbuffer matrixBuffer 
{
    matrix worldViewProjectionMatrix;
    matrix worldMatrix;
};


// Define a constant buffer for camera position
cbuffer cameraBuffer
{
    float3 cameraPosition;
    float pad;
};

// Define the input structure for vertex data
struct VertexInput
{
    float3 position : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
};

// Define the output structure for vertex data
struct VertexOutput
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD0;
    float3 normal : NORMAL;
    float3 viewDirection : TEXCOORD1;
};


// Define the main function for the vertex shader
VertexOutput main(VertexInput IN)
{
	VertexOutput OUT;
	float4 worldPosition = float4(0, 0, 0, 0);
    
	float4 newPos = float4(IN.position.xyz, 1.0f);
	newPos.w = 1.0f;
    
	OUT.position = mul(worldViewProjectionMatrix, newPos);
    
	OUT.uv = IN.uv;
    
	OUT.normal = mul(IN.normal, (float3x3) worldMatrix);
	OUT.normal = normalize(OUT.normal);
   
	OUT.viewDirection = cameraPosition.xyz - IN.position;
	OUT.viewDirection = normalize(OUT.viewDirection);
    

    
    
    return OUT;
}