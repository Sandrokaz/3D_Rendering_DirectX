#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include "MeshData.h"
#include <iostream>

#pragma comment(lib, "assimp")
using namespace DirectX;


class Mesh
{
public:
	INT init(ID3D11Device* pD3DDevice, int descr, const CHAR* filename, XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scale);
	void render(ID3D11DeviceContext* pD3DDeviceContext);
	void update(FLOAT deltaTime);
	//void UpdateMovement(FLOAT deltaTime);
	void setPos(FLOAT X, FLOAT Y, FLOAT Z);
	void setRot(FLOAT X, FLOAT Y, FLOAT Z);
	void setScale(FLOAT X, FLOAT Y, FLOAT Z);
	

	BOOL IsInitialised = FALSE;
	XMFLOAT4X4* getWorldMatrix() { return &_worldMatrix; }
	void deInit();

private:
	INT initVertexBuffer(ID3D11Device* pD3DDevice, int descr);
	INT initIndexBuffer(ID3D11Device* pD3DDevice, int descr);

	ID3D11Buffer* _pVertexBuffer = nullptr;
	ID3D11Buffer* _pIndexBuffer = nullptr;

	UINT _vertexCount = 0; // amount of vertices
	UINT _vertexStride = 0; // size of one vertex
	UINT _indexCount = 0; // amount of indices

	XMFLOAT4X4 _worldMatrix = {}; // world transformation matrix

	float _posX;
	float _posY;
	float _posZ;
	float _rotX;
	float _rotY;
	float _rotZ;
	float _scaleX = 1;
	float _scaleY = 1;
	float _scaleZ = 1;


	
	std::unique_ptr<Cube> cube = std::make_unique<Cube>();
	std::unique_ptr<Tetrahedron> tetrahedron = std::make_unique<Tetrahedron>();
	std::unique_ptr<PentagonalPrism> pentagonalPrism = std::make_unique<PentagonalPrism>();

};

