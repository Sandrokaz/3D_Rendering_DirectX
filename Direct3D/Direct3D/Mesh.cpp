#include "Mesh.h"
#include "Utils.h"
#include "Vertex.h"
#include <xutility>
#include "resource.h"



INT Mesh::init(ID3D11Device* pD3DDevice, int descr)
{
	INT error = initVertexBuffer(pD3DDevice, descr);
	CheckError(error);

	error = initIndexBuffer(pD3DDevice, descr);
	CheckError(error);

	IsInitialised = TRUE;

	// initialize world transformation matrix
	XMStoreFloat4x4(&_worldMatrix, XMMatrixIdentity());

	return 0;
}


void Mesh::render(ID3D11DeviceContext* pD3DDeviceContext)
{
	// set mesh data
	static UINT offset = 0;
	pD3DDeviceContext->IASetVertexBuffers(0, 1, &_pVertexBuffer, &_vertexStride, &offset);
	pD3DDeviceContext->IASetIndexBuffer(_pIndexBuffer, DXGI_FORMAT_R16_UINT, offset);
	pD3DDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// draw with index buffer
	pD3DDeviceContext->DrawIndexed(_indexCount, 0, 0);
}

void Mesh::UpdateMovement(FLOAT deltaTime)
{

	FLOAT move = 5.0f * deltaTime;
	if (((GetAsyncKeyState(VK_SPACE) & 0x8000)))
	{

		if ((GetAsyncKeyState(VK_UP) & 0x8000) || (GetAsyncKeyState('W') & 0x8000)) _rotX += XM_PI / 6.0f * deltaTime;
		if ((GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState('S') & 0x8000))  _rotX -= XM_PI / 6.0f * deltaTime;
		if ((GetAsyncKeyState(VK_LEFT) & 0x8000) || (GetAsyncKeyState('A') & 0x8000))  _rotY -= XM_PI / 6.0f * deltaTime;
		if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) || (GetAsyncKeyState('D') & 0x8000)) _rotY += XM_PI / 6.0f * deltaTime;
	}
	else
	{

		if ((GetAsyncKeyState(VK_UP) & 0x8000) || (GetAsyncKeyState('W') & 0x8000))  _posY += move;
		if ((GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState('S') & 0x8000)) _posY -= move;
		if ((GetAsyncKeyState(VK_LEFT) & 0x8000) || (GetAsyncKeyState('A') & 0x8000)) _posX -= move;
		if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) || (GetAsyncKeyState('D') & 0x8000)) _posX += move;
		if ((GetAsyncKeyState(VK_SUBTRACT) & 0x8000) || (GetAsyncKeyState('Q') & 0x8000)) _posZ -= move;
		if ((GetAsyncKeyState(VK_ADD) & 0x8000) || (GetAsyncKeyState('E') & 0x8000))  _posZ += move;

	}

	XMMATRIX translation = XMMatrixTranslation(_posX, _posY, _posZ);
	XMMATRIX rotation = XMMatrixRotationRollPitchYaw(_rotX, _rotY, _rotZ);				
	XMMATRIX localScale = XMMatrixScaling(_scaleX, _scaleY, _scaleZ);
	XMStoreFloat4x4(&_worldMatrix, localScale * rotation * translation);
}



void Mesh::setPos(FLOAT X, FLOAT Y, FLOAT Z)
{
	_posX = X;
	_posY = Y;
	_posZ = Z;
}

void Mesh::setRot(FLOAT X, FLOAT Y, FLOAT Z)
{
	_rotX += X;
	_rotY += Y;
	_rotZ += Z;
}

void Mesh::setScale(FLOAT X, FLOAT Y, FLOAT Z)
{
	_scaleX = X;
	_scaleY = Y;
	_scaleZ = Z;
}

void Mesh::setDefaultPos(FLOAT X, FLOAT Y, FLOAT Z)
{
	_posX = X;
	_posY = Y;
	_posZ = Z;
}

void Mesh::deInit()
{
	safeRelease<ID3D11Buffer>(_pVertexBuffer);
	safeRelease<ID3D11Buffer>(_pIndexBuffer);
	IsInitialised = FALSE;
}

INT Mesh::initVertexBuffer(ID3D11Device* pD3DDevice, int descr)
{
	Vertex* vertices = nullptr;


	switch (descr)
	{

	case IDC_CUBE:
		vertices = cube.get()->vertices;
		_vertexCount = std::size(cube.get()->vertices);
		break;
	case IDC_Tetrahedron:
		vertices = tetrahedron.get()->vertices;
		_vertexCount = std::size(tetrahedron.get()->vertices);
		break;
	case IDC_PentagonalPrism:
		vertices = pentagonalPrism.get()->vertices;
		_vertexCount = std::size(pentagonalPrism.get()->vertices);
		break;
	default:
		break;
	}

	_vertexStride = sizeof(Vertex);
	D3D11_BUFFER_DESC desc = {};
	desc.ByteWidth = _vertexCount * _vertexStride;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER; // buffer type
	desc.Usage = D3D11_USAGE_IMMUTABLE; // who has which access

	D3D11_SUBRESOURCE_DATA initialData = {};
	initialData.pSysMem = vertices;

	HRESULT hr = pD3DDevice->CreateBuffer(&desc, &initialData, &_pVertexBuffer);
	CheckFailed(hr, 30);

	return 0;
}

INT Mesh::initIndexBuffer(ID3D11Device* pD3DDevice, int descr)
{
	
	USHORT* indices = nullptr;
	switch (descr)
	{
	case IDC_CUBE:
	indices = cube.get()->indices;
	_indexCount = std::size(cube.get()->indices);
	break;

	case IDC_Tetrahedron:
		indices = tetrahedron.get()->indices;
		_indexCount = std::size(tetrahedron.get()->indices);
		break;

	case IDC_PentagonalPrism:
		indices = pentagonalPrism.get()->indices;
		_indexCount = std::size(pentagonalPrism.get()->indices);
		break;

	default:
		break;
	}



	D3D11_BUFFER_DESC desc = {};
	desc.ByteWidth = _indexCount * sizeof(USHORT);
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.Usage = D3D11_USAGE_IMMUTABLE;

	D3D11_SUBRESOURCE_DATA initialData = {};
	initialData.pSysMem = indices;

	HRESULT hr = pD3DDevice->CreateBuffer(&desc, &initialData, &_pIndexBuffer);
	CheckFailed(hr, 32);

	return 0;
}
