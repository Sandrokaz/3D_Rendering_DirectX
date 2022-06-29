#pragma once
#include <d3d11.h>
#include <DirectXMath.h>


#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;

class Material
{
public:
	INT Initialize(ID3D11Device* pD3DDevice, int texture, int desc);
	void Render(ID3D11DeviceContext* pD3DDeviceContext, XMFLOAT4X4* pWorldMatrix, XMFLOAT4X4* pViewMatrix, XMFLOAT4X4* pProjectionMatrix);
	void DeInitialize();
	BOOL IsInitialized = FALSE;

private:
	INT CreateVertexShader(ID3D11Device* pD3DDevice,  int desc);
	INT CreatePixelShader(ID3D11Device* pD3DDevice, int desc);
	INT CreateInputLayout(ID3D11Device* pD3DDevice, ID3DBlob* pVertexShaderData); // exchange for flexible vertex format
	INT CreateMatrixBuffer(ID3D11Device* pD3DDevice);
	INT CreateTexAndSampler(ID3D11Device* pD3DDevice, LPCTSTR textureName);
	void SetMatrices(ID3D11DeviceContext* pD3DDeviceContext, XMFLOAT4X4* pWorldMatrix, XMFLOAT4X4* pViewMatrix, XMFLOAT4X4* pProjectionMatrix);

	ID3D11VertexShader* _pVertexShader = nullptr;
	ID3D11PixelShader* _pPixelShader = nullptr;
	ID3D11InputLayout* _pInputLayout = nullptr; // describe vertex layout

	ID3D11ShaderResourceView* _pTexture = nullptr;
	ID3D11SamplerState* _pSamplerState = nullptr;
	
	ID3D11Buffer* _pMatrixBuffer = nullptr; 

	struct MatrixBuffer
	{
		XMFLOAT4X4 worldViewProjectionMatrix;
		XMFLOAT4X4 worldMatrix;
	};

};

