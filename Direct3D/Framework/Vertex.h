#pragma once
//#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

struct Vertex
{
	Vertex()
	{
		position = XMFLOAT3{ 0.0f, 0.0f, 0.0f };
		uv = XMFLOAT2{ 0.0f, 0.0f };
		normal = XMFLOAT3{ 0.0f, 0.0f, 0.0f };
		tangent = XMFLOAT3{ 0.0f,0.0f,0.0f };
		
	}




	XMFLOAT3 position;
	XMFLOAT2 uv;
	XMFLOAT3 normal;
	XMFLOAT3 tangent;

	Vertex(FLOAT x, FLOAT y, FLOAT z, FLOAT u, FLOAT v, FLOAT nx, FLOAT ny, FLOAT nz,FLOAT tx, FLOAT ty, FLOAT tz) : position(x, y, z), uv(u, v), normal(nx, ny, nz),tangent(tx, ty, tz) {}
};