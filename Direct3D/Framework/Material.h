#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include "LightBuffer.h"
#include <DirectXMath.h>


//#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;

class Material
{
public:
	INT init(ID3D11Device* pD3DDevice, LPCWSTR textureName, LPCWSTR vertexFilePath, LPCWSTR pixelFilePath);
	void render(ID3D11DeviceContext* pD3DDeviceContext);//, XMFLOAT4X4* pWorldMatrix, XMFLOAT4X4* pViewMatrix, XMFLOAT4X4* pProjectionMatrix);
	void deInit();
	BOOL IsInitialized = FALSE;

	INT setLight(ID3D11DeviceContext* pD3DDeviceContext, const LightBuffer& light);
	INT setMatrices(ID3D11DeviceContext* pD3DDeviceContext, XMFLOAT4X4 pWorldMatrix, XMFLOAT4X4 pViewMatrix, XMFLOAT4X4 pProjectionMatrix, XMFLOAT3 pCameraPos);

private:
	INT createVertexShader(ID3D11Device* pD3DDevice, LPCWSTR vertexFilePath);
	INT createPixelShader(ID3D11Device* pD3DDevice, LPCWSTR pixelFilePath);
	INT createInputLayout(ID3D11Device* pD3DDevice, ID3DBlob* pVertexShaderData); // exchange for flexible vertex format
	INT createMatrixBuffer(ID3D11Device* pD3DDevice);
	INT createTextureAndSampler(ID3D11Device* pD3DDevice, LPCTSTR textureName);
	INT createLightBuffer(ID3D11Device* pD3DDevice);					  
	INT createCameraBuffer(ID3D11Device* pD3DDevice);

	ID3D11VertexShader* _pVertexShader = nullptr;
	ID3D11PixelShader* _pPixelShader = nullptr;
	ID3D11InputLayout* _pInputLayout = nullptr; // describe vertex layout

	ID3D11ShaderResourceView* _pTexture = nullptr;
	ID3D11SamplerState* _pSamplerState = nullptr;
	
	ID3D11Buffer* _pMatrixBuffer = nullptr; 
	ID3D11Buffer* _pLightBuffer = nullptr;
	ID3D11Buffer* _pCameraBuffer = nullptr;

	struct MatrixBuffer
	{
		XMFLOAT4X4 worldViewProjectionMatrix;
		XMFLOAT4X4 worldMatrix;
		
	};

	struct CameraBuffer
	{
		XMFLOAT3 cameraPosition;
		FLOAT pad;
	};




};

