#pragma once
#include <d3d11.h>
#include "Vertex.h"
#include <DirectXMath.h>
#include <vector>

//#pragma comment(lib, "assimp-vc140-mtd.lib")
#pragma comment(lib, "assimp.lib")

using namespace std;
using namespace DirectX;
							  

class Mesh
{
public:
	Mesh();

	INT init(ID3D11Device* pD3DDevice, const CHAR* filename, XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scale);

	void update(FLOAT deltaTime);
	void render(ID3D11DeviceContext* pD3DDeviceContext);
	//void UpdateMovement(FLOAT deltaTime);

	// Set floats
	void setPos(FLOAT X, FLOAT Y, FLOAT Z);
	void setRot(FLOAT X, FLOAT Y, FLOAT Z);
	void setScale(FLOAT X, FLOAT Y, FLOAT Z);


	// Set vectors
	void setPos(XMVECTOR _position);
	void setRot(XMVECTOR _rotation);
	void setScale(XMVECTOR _scale);


	// Adjust  floats
	void adjustPosition(FLOAT x, FLOAT y, FLOAT z);
	void adjustRotation(FLOAT x, FLOAT y, FLOAT z);
	void adjustScale(FLOAT x, FLOAT y, FLOAT z);

	// Adjust vectors
	void adjustPosition(XMVECTOR _position);
	void adjustRotation(XMVECTOR _rotation);
	void adjustScale(XMVECTOR _scale);


	BOOL IsInitialised = FALSE;


	//XMFLOAT3 getPositionFloat3() { return _positionFloat3; }
	//XMFLOAT3 getRotationFloat3() { return _rotationFloat3; }
	//XMFLOAT3 getScaleFloat3() { return _scaleFloat3; }


	//XMVECTOR getPositionVector() { return _positionVector; }
	//XMVECTOR getRotationVector() { return _rotationVector; }
	//XMVECTOR getScaleVector() { return _scaleVector; }


	XMFLOAT4X4 getWorldMatrix4x4() { return _worldMatrix4x4; }
	XMMATRIX getWorldMatrix() { return _worldMatrix; }


	void deInit();

private:
	ID3D11Buffer* _pVertexBuffer = nullptr;
	ID3D11Buffer* _pIndexBuffer = nullptr;


	INT initVertexBuffer(Vertex vertices[],ID3D11Device* pD3DDevice);
	INT initIndexBuffer(WORD indices[],ID3D11Device* pD3DDevice);

	void updateTransform();

	UINT _vertexCount = 0; // amount of vertices
	UINT _vertexStride = 0; // size of one vertex
	UINT _indexCount = 0; // amount of indices


	XMFLOAT4X4 _worldMatrix4x4 = {};
	XMMATRIX _worldMatrix = {};


	XMFLOAT3 _positionFloat3;
	XMVECTOR _positionVector;
	XMFLOAT3 _rotationFloat3;
	XMVECTOR _rotationVector;
	XMFLOAT3 _scaleFloat3;
	XMVECTOR _scaleVector;
};

