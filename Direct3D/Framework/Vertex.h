#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

struct Vertex
{
	Vertex()
	{
		position = XMFLOAT3{ 0.0f, 0.0f, 0.0f };
		uv = XMFLOAT2{ 0.0f, 0.0f };
		normal = XMFLOAT3{ 0.0f, 0.0f, 0.0f };
		//color = XMFLOAT4{ 0.0f, 0.0f, 0.0f, 0.0f };
	}




	XMFLOAT3 position;
	XMFLOAT2 uv;
	XMFLOAT3 normal;
	//XMFLOAT4 color;

	//Vertex(FLOAT x, FLOAT y, FLOAT z) : position(x, y, z), normal(0.0f, 0.0f, 0.0f), uv(0.0f, 0.0f), color(1.0f, 1.0f, 1.0f, 1.0f) {}
	//Vertex(FLOAT x, FLOAT y, FLOAT z, FLOAT r, FLOAT g, FLOAT b) : position(x, y, z), normal(0.0f, 0.0f, 0.0f), uv(0.0f, 0.0f), color(r, g, b, 1.0f) {}
	//Vertex(FLOAT x, FLOAT y, FLOAT z, UINT r, UINT g, UINT b) : position(x, y, z), normal(0.0f, 0.0f, 0.0f), uv(0.0f, 0.0f), color(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f) {}
	//Vertex(FLOAT x, FLOAT y, FLOAT z, FLOAT u, FLOAT v) : position(x, y, z), normal(0.0f, 0.0f, 0.0f), uv(u, v), color(1.0f, 1.0f, 1.0f, 1.0f) {}
	Vertex (FLOAT x, FLOAT y, FLOAT z, FLOAT u, FLOAT v, FLOAT nx, FLOAT ny, FLOAT nz) : position(x, y, z), uv(u, v), normal(nx, ny, nz)  {}
};