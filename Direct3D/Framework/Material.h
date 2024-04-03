#pragma once
#include <d3d11.h>
#include "LightBuffer.h"
#include <DirectXMath.h>
#include <string>



using namespace DirectX;

class Material
{
public:
	INT init(ID3D11Device* pD3DDevice, LPCWSTR textureName, LPCWSTR normalTextureName, LPCWSTR vertexFilePath, LPCWSTR pixelFilePath);
	void render(ID3D11DeviceContext* pD3DDeviceContext);
	void deInit();


	INT setMatrices(ID3D11DeviceContext* pD3DDeviceContext, XMFLOAT4X4 pWorldMatrix, XMFLOAT4X4 pViewMatrix, XMFLOAT4X4 pProjectionMatrix, XMFLOAT3 pCameraPos);
	INT setLight(ID3D11DeviceContext* pD3DDeviceContext, const LightBuffer& light);
private:
	INT createVertexShader(ID3D11Device* pD3DDevice, LPCWSTR vertexFilePath);
	INT createPixelShader(ID3D11Device* pD3DDevice, LPCWSTR pixelFilePath);
	INT createInputLayout(ID3D11Device* pD3DDevice, ID3DBlob* pVertexShaderData); 
	INT createMatrixBuffer(ID3D11Device* pD3DDevice);
	INT createCameraBuffer(ID3D11Device* pD3DDevice);
	INT createLightBuffer(ID3D11Device* pD3DDevice);
	BOOL hasKnownTextureType(const std::wstring& textureName);
	INT createTextureAndSampler(ID3D11Device* pD3DDevice, LPCWSTR textureName, LPCWSTR normalTextureName);


	ID3D11VertexShader* _pVertexShader = nullptr;
	ID3D11PixelShader* _pPixelShader = nullptr;
	ID3D11InputLayout* _pInputLayout = nullptr; 

	ID3D11ShaderResourceView* _pMainTexture = nullptr;
	ID3D11SamplerState* _pMainSampler = nullptr;
	ID3D11ShaderResourceView* _pNormalTexture = nullptr;
	ID3D11SamplerState* _pNormalSampler = nullptr;


	
	ID3D11Buffer* _pMatrixBuffer = nullptr; 
	ID3D11Buffer* _pCameraBuffer = nullptr;
	ID3D11Buffer* _pLightBuffer = nullptr;

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

