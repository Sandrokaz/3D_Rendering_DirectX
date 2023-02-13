#include "Material.h"
#include "WICTextureLoader.h"
#include "Utilities.h"
#include "resource.h"
#include <d3dcompiler.h>

using namespace DirectX;

INT Material::Initialize(ID3D11Device* pD3DDevice, int texture, int desc)
{
	INT error = CreateVertexShader(pD3DDevice, desc);
	CheckError(error);

	error = CreatePixelShader(pD3DDevice, desc);
	CheckError(error);

	error = CreateMatrixBuffer(pD3DDevice);
	CheckError(error);
	

	error = CreateLightBuffer(pD3DDevice);
	CheckError(error);


	

	CheckError(error);

	IsInitialized = TRUE;

	return 0;
}

void Material::Render(ID3D11DeviceContext* pD3DDeviceContext, XMFLOAT4X4* pWorldMatrix, XMFLOAT4X4* pViewMatrix, XMFLOAT4X4* pProjectionMatrix)
{
	// set texture and sampler state
	pD3DDeviceContext->PSSetShaderResources(0, 1, &_pTexture);
	pD3DDeviceContext->PSSetSamplers(0, 1, &_pSamplerState);

	//// set material
	//pD3DDevice->SetMaterial(&_material);

	// set shader pipeline
	pD3DDeviceContext->VSSetShader(_pVertexShader, nullptr, 0);
	pD3DDeviceContext->PSSetShader(_pPixelShader, nullptr, 0);
	pD3DDeviceContext->IASetInputLayout(_pInputLayout);

	// set matrices
	SetMatrices(pD3DDeviceContext, pWorldMatrix, pViewMatrix, pProjectionMatrix);
}
void Material::DeInitialize()
{
	IsInitialized = FALSE;
	safeRelease<ID3D11ShaderResourceView>(_pTexture);
	safeRelease<ID3D11SamplerState>(_pSamplerState);
	safeRelease<ID3D11Buffer>(_pMatrixBuffer);
	safeRelease<ID3D11InputLayout>(_pInputLayout);
	safeRelease<ID3D11VertexShader>(_pVertexShader);
	safeRelease<ID3D11PixelShader>(_pPixelShader);
}

void Material::SetMatrices(ID3D11DeviceContext* pD3DDeviceContext, XMFLOAT4X4* pWorldMatrix, XMFLOAT4X4* pViewMatrix, XMFLOAT4X4* pProjectionMatrix)
{
		XMMATRIX worldMatrix = XMLoadFloat4x4(pWorldMatrix);
		XMMATRIX viewMatrix = XMLoadFloat4x4(pViewMatrix);
		XMMATRIX projectionMatrix = XMLoadFloat4x4(pProjectionMatrix);


		XMMATRIX wvpMatrix = XMMatrixTranspose(worldMatrix * viewMatrix * projectionMatrix); // transpose because of column mayor - row mayor problem

		D3D11_MAPPED_SUBRESOURCE data = {};
		HRESULT hr = pD3DDeviceContext->Map(_pMatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
		if (FAILED(hr)) return;

		MatrixBuffer* pMatrixBuffer = static_cast<MatrixBuffer*>(data.pData);
		XMStoreFloat4x4(&(pMatrixBuffer->worldViewProjectionMatrix), wvpMatrix);
		XMStoreFloat4x4(&(pMatrixBuffer->worldMatrix), XMMatrixTranspose(worldMatrix));

		pD3DDeviceContext->Unmap(_pMatrixBuffer, 0);

		pD3DDeviceContext->VSSetConstantBuffers(0, 1, &_pMatrixBuffer);
}



INT Material::setLight(ID3D11DeviceContext* pD3DDeviceContext, const LightBuffer& light)
{
	D3D11_MAPPED_SUBRESOURCE data;
	ZeroMemory(&data, sizeof(data));
	HRESULT hr = pD3DDeviceContext->Map(_pLightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
	CheckFailed(hr, 88);

	LightBuffer* pLight = reinterpret_cast<LightBuffer*>(data.pData);
	*pLight = light;

	pD3DDeviceContext->Unmap(_pLightBuffer, 0);
	pD3DDeviceContext->PSSetConstantBuffers(0, 1, &_pLightBuffer);
	//return 0;
}





INT Material::CreateVertexShader(ID3D11Device* pD3DDevice, int desc)
{
	ID3DBlob* pCompiledShaderCode = nullptr;

	// load already compiled shader
	HRESULT hr = {};
	//HRESULT hr = D3DReadFileToBlob(TEXT("ColorVertexShader.cso"), &pCompiledShaderCode);
	//HRESULT hr = D3DReadFileToBlob(TEXT("TextureVertexShader.cso"), &pCompiledShaderCode);
	//HRESULT hr = D3DReadFileToBlob(TEXT("PhongVertexShader.cso"), &pCompiledShaderCode);
	CheckFailed(hr, 62);
	
	// create shader object
	hr = pD3DDevice->CreateVertexShader(pCompiledShaderCode->GetBufferPointer(), pCompiledShaderCode->GetBufferSize(), nullptr, &_pVertexShader);
	CheckFailed(hr, 64);

	INT error = CreateInputLayout(pD3DDevice, pCompiledShaderCode);
	CheckError(error);

	safeRelease<ID3DBlob>(pCompiledShaderCode);

	return 0;
}

INT Material::CreatePixelShader(ID3D11Device* pD3DDevice,int desc)
{
	ID3DBlob* pCompiledShaderCode = nullptr;

	HRESULT hr = {};	
	

	//HRESULT hr = D3DReadFileToBlob(TEXT("ColorPixelShader.cso"), &pCompiledShaderCode);
	//HRESULT hr = D3DReadFileToBlob(TEXT("TexturePixelShader.cso"), &pCompiledShaderCode);
	//HRESULT hr = D3DReadFileToBlob(TEXT("PhongPixelShader.cso"), &pCompiledShaderCode);
	CheckFailed(hr, 66);

	hr = pD3DDevice->CreatePixelShader(pCompiledShaderCode->GetBufferPointer(), pCompiledShaderCode->GetBufferSize(), nullptr, &_pPixelShader);
	CheckFailed(hr, 68);

	safeRelease<ID3DBlob>(pCompiledShaderCode);

	return 0;
}

INT Material::CreateInputLayout(ID3D11Device* pD3DDevice, ID3DBlob* pVertexShaderData)
{
	
	D3D11_INPUT_ELEMENT_DESC elements[5] = {};

	// position
	elements[0].SemanticName = "POSITION";
	elements[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;

	// normal
	elements[1].SemanticName = "NORMAL";
	elements[1].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	elements[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

	// uv
	elements[2].SemanticName = "TEXCOORD";
	elements[2].Format = DXGI_FORMAT_R32G32_FLOAT;
	elements[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

	elements[3].SemanticName = "TEXCOORD";
	elements[3].SemanticIndex = 1;
	elements[3].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	elements[3].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

	// color
	elements[4].SemanticName = "COLOR";
	elements[4].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	elements[4].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

	HRESULT hr = pD3DDevice->CreateInputLayout(elements, 5, pVertexShaderData->GetBufferPointer(), pVertexShaderData->GetBufferSize(), &_pInputLayout);
	CheckFailed(hr, 70);

	return 0;
}

INT Material::CreateMatrixBuffer(ID3D11Device* pD3DDevice)
{
	D3D11_BUFFER_DESC desc = {};
	desc.ByteWidth = sizeof(MatrixBuffer);
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	HRESULT hr = pD3DDevice->CreateBuffer(&desc, nullptr, &_pMatrixBuffer);
	CheckFailed(hr, 74);

	return 0;
}


INT Material::CreateLightBuffer(ID3D11Device* pD3DDevice)
{
	D3D11_BUFFER_DESC desc = {};
	desc.ByteWidth = sizeof(LightBuffer);
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	HRESULT hr = pD3DDevice->CreateBuffer(&desc, nullptr, &_pLightBuffer);
	CheckFailed(hr, 67);

	return 0;
}





INT Material::CreateTexAndSampler(ID3D11Device* pD3DDevice, LPCTSTR textureName)
{
	// create texture
	HRESULT hr = CreateWICTextureFromFile(pD3DDevice, textureName, nullptr, &_pTexture);
	CheckFailed(hr, 76);

	// create sampler state
	D3D11_SAMPLER_DESC desc = {};
	desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;

	hr = pD3DDevice->CreateSamplerState(&desc, &_pSamplerState);
	CheckFailed(hr, 78);
	
	return 0;
}
