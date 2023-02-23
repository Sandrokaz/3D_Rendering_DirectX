// Define a constant buffer for matrices used to transform vertices
cbuffer matrixBuffer : register(b0)
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
    float4 position : SV_Position;
    float2 uv : TEXCOOD0;
    float3 normal : NORMAL;
    float3 viewDirection : TEXTCOORD1;
};


// Define the main function for the vertex shader
VertexOutput main(VertexInput input)
{
    VertexOutput output;

    float4 worldPosition = float4(0, 0, 0, 0);
    float4 newPos = float4(input.position.xyz, 1.0f);
    newPos.w = 1.0f;

    output.position = mul(worldViewProjectionMatrix, newPos);   // Multiply the vertex position by the world-view-projection matrix to get the final screen position

    output.uv = input.uv; // Copy the texture coordinates to the output

    
    output.normal = mul(input.normal, (float3x3) worldMatrix);   // Multiply the normal vector by the world matrix to get the final normal vector in world space
    output.normal = normalize(output.normal);  

    //worldPosition = mul(newPos, worldMatrix);
   
    output.viewDirection = cameraPosition.xyz - input.position;        //Calculate the direction vector from the vertex to the camera
    output.viewDirection = normalize(output.viewDirection);      // Normalize the direction vector

    return output;
}