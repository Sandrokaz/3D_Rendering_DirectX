#include "Material.h"
#include "WICTextureLoader.h"
#include "DDSTextureLoader.h"
#include "Utilities.h"
#include <d3dcompiler.h>


#pragma comment(lib, "d3dcompiler.lib")



INT Material::init(ID3D11Device* pD3DDevice, LPCWSTR textureName, LPCWSTR normalTextureName, LPCWSTR vertexFilePath, LPCWSTR pixelFilePath)
{
	INT error = createVertexShader(pD3DDevice, vertexFilePath);
	CheckError(error);

	error = createPixelShader(pD3DDevice, pixelFilePath);
	CheckError(error);

	error = createMatrixBuffer(pD3DDevice);
	CheckError(error);

	error = createCameraBuffer(pD3DDevice);
	CheckError(error);
	
	error = createLightBuffer(pD3DDevice);
	CheckError(error);

	error = createTextureAndSampler( pD3DDevice, textureName, normalTextureName);
	CheckError(error);
	



	return 0;
}

void Material::render(ID3D11DeviceContext* pD3DDeviceContext)
{
	// set texture and sampler state 
	pD3DDeviceContext->PSSetShaderResources(0, 1, &_pMainTexture);
	pD3DDeviceContext->PSSetSamplers(0, 1, &_pMainSampler);

	if (_pNormalTexture != nullptr)
	{
	pD3DDeviceContext->PSSetShaderResources(1, 1, &_pNormalTexture);
	pD3DDeviceContext->PSSetSamplers(1, 1, &_pNormalSampler);

	}




	// set shader pipeline
	pD3DDeviceContext->IASetInputLayout(_pInputLayout);
	pD3DDeviceContext->VSSetShader(_pVertexShader, nullptr, 0);
	pD3DDeviceContext->PSSetShader(_pPixelShader, nullptr, 0);

	
}
void Material::deInit()
{

	safeRelease<ID3D11ShaderResourceView>(_pMainTexture);
	safeRelease<ID3D11SamplerState>(_pMainSampler);
	safeRelease<ID3D11ShaderResourceView>(_pNormalTexture);
	safeRelease<ID3D11SamplerState>(_pNormalSampler);
	safeRelease<ID3D11Buffer>(_pMatrixBuffer);
	safeRelease<ID3D11Buffer>(_pLightBuffer);
	safeRelease<ID3D11InputLayout>(_pInputLayout);
	safeRelease<ID3D11VertexShader>(_pVertexShader);
	safeRelease<ID3D11PixelShader>(_pPixelShader);
}

INT Material::setMatrices(ID3D11DeviceContext* pD3DDeviceContext, XMFLOAT4X4 pWorldMatrix, XMFLOAT4X4 pViewMatrix, XMFLOAT4X4 pProjectionMatrix, XMFLOAT3 pCameraPos)
{

		HRESULT hr;
		D3D11_MAPPED_SUBRESOURCE data = {};
		ZeroMemory(&data, sizeof(data));
	    unsigned int bufferNum;
	

		hr = pD3DDeviceContext->Map(_pMatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
		CheckFailed(hr, 56);

		XMMATRIX worldMatrix = XMLoadFloat4x4(&pWorldMatrix);
		XMMATRIX viewMatrix = XMLoadFloat4x4(&pViewMatrix);
		XMMATRIX projectionMatrix = XMLoadFloat4x4(&pProjectionMatrix);
		XMMATRIX wvpMatrix = worldMatrix * viewMatrix * projectionMatrix; 


		// Setup  Matrix and Camera Buffer parameters
		MatrixBuffer* pMatrixBuffer = reinterpret_cast<MatrixBuffer*>(data.pData);	    
		XMStoreFloat4x4(&(pMatrixBuffer->worldViewProjectionMatrix), wvpMatrix);
		XMStoreFloat4x4(&(pMatrixBuffer->worldMatrix), XMMatrixTranspose(worldMatrix));

		pD3DDeviceContext->Unmap(_pMatrixBuffer, 0);
		pD3DDeviceContext->VSSetConstantBuffers(0, 1, &_pMatrixBuffer);

		// Setup Camera Buffer Params
		hr = pD3DDeviceContext->Map(_pCameraBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
		CheckFailed(hr, 58);


		CameraBuffer* cameraBuffer = reinterpret_cast<CameraBuffer*>(data.pData);
		cameraBuffer->cameraPosition = pCameraPos;
		cameraBuffer->pad = 0;
	
	
		pD3DDeviceContext->Unmap(_pCameraBuffer, 0);
		bufferNum = 1;
		pD3DDeviceContext->VSSetConstantBuffers(bufferNum, 1, &_pCameraBuffer); 

}



INT Material::setLight(ID3D11DeviceContext* pD3DDeviceContext, const LightBuffer& light)
{
	D3D11_MAPPED_SUBRESOURCE data;
	ZeroMemory(&data, sizeof(data));
	HRESULT hr = pD3DDeviceContext->Map(_pLightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
	CheckFailed(hr, 60);

	LightBuffer* pLight = reinterpret_cast<LightBuffer*>(data.pData);
	*pLight = light;

	pD3DDeviceContext->Unmap(_pLightBuffer, 0);
	pD3DDeviceContext->PSSetConstantBuffers(0, 1, &_pLightBuffer);

}





INT Material::createVertexShader(ID3D11Device* pD3DDevice, LPCWSTR vertexFilePath)
{
	ID3DBlob* pCompiledShaderCode = nullptr;
	HRESULT hr = D3DReadFileToBlob(vertexFilePath, &pCompiledShaderCode);
	CheckFailed(hr, 62);
	

	hr = pD3DDevice->CreateVertexShader(pCompiledShaderCode->GetBufferPointer(), pCompiledShaderCode->GetBufferSize(), nullptr, &_pVertexShader);
	CheckFailed(hr, 64);
	INT error = createInputLayout(pD3DDevice, pCompiledShaderCode);
	CheckError(error);

	safeRelease<ID3DBlob>(pCompiledShaderCode);

	return 0;
}

INT Material::createPixelShader(ID3D11Device* pD3DDevice, LPCWSTR pixelFilePath)
{
	ID3DBlob* pCompiledShaderCode = nullptr;
	HRESULT hr = D3DReadFileToBlob(pixelFilePath, &pCompiledShaderCode);;
	CheckFailed(hr, 66);

	hr = pD3DDevice->CreatePixelShader(pCompiledShaderCode->GetBufferPointer(), pCompiledShaderCode->GetBufferSize(), nullptr, &_pPixelShader);
	CheckFailed(hr, 68);

	safeRelease<ID3DBlob>(pCompiledShaderCode);

	return 0;
}

INT Material::createInputLayout(ID3D11Device* pD3DDevice, ID3DBlob* pVertexShaderData)
{

	
		  // Declarating input layout with byte offset
	
	D3D11_INPUT_ELEMENT_DESC elements[] =
	{
		// position
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },

		// uv
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },

		// normal
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 }	,

		// tangent
		{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 },

		// bitangent
		{ "BITANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 44, D3D11_INPUT_PER_VERTEX_DATA, 0 },

		// View Direction
		{ "TEXCOORD", 1, DXGI_FORMAT_R32G32B32_FLOAT, 0, 56, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	
	UINT numElements = ARRAYSIZE(elements);

	HRESULT hr = pD3DDevice->CreateInputLayout(elements, numElements, pVertexShaderData->GetBufferPointer(), pVertexShaderData->GetBufferSize(), &_pInputLayout);
	CheckFailed(hr, 69);

	return 0;

}

INT Material::createMatrixBuffer(ID3D11Device* pD3DDevice)
{
	D3D11_BUFFER_DESC desc = {};
	desc.ByteWidth = sizeof(MatrixBuffer);
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.Usage = D3D11_USAGE_DYNAMIC;  // or default
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	// or 0


	HRESULT hr = pD3DDevice->CreateBuffer(&desc, nullptr, &_pMatrixBuffer);
	CheckFailed(hr, 72);

	return 0;
}

INT Material::createCameraBuffer(ID3D11Device* _pD3DDevice)
{
	D3D11_BUFFER_DESC desc = {};
	desc.ByteWidth = sizeof(CameraBuffer);
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	HRESULT hr = _pD3DDevice->CreateBuffer(&desc, nullptr, &_pCameraBuffer);
	CheckFailed(hr, 74);

	return 0;
}

INT Material::createLightBuffer(ID3D11Device* pD3DDevice)
{
	D3D11_BUFFER_DESC desc = {};
	desc.ByteWidth = sizeof(LightBuffer);
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	HRESULT hr = pD3DDevice->CreateBuffer(&desc, nullptr, &_pLightBuffer);
	CheckFailed(hr, 76);

	return 0;
}

BOOL Material::hasKnownTextureType(const std::wstring& textureName)
{
	if (textureName.length() >= 20)
	{
		std::wstring suffix = textureName.substr(textureName.length() - 4);
		if (suffix == L".dds" || suffix == L".png" || suffix == L".jpg" || suffix == L".jpeg")
		{
			return true;
		}
	}
	return false;

}



INT Material::createTextureAndSampler(ID3D11Device* pD3DDevice, LPCWSTR  textureName, LPCWSTR normalTextureName)
{
	HRESULT hr = S_OK;

	// Load the main texture
	hr = CreateWICTextureFromFile(pD3DDevice, textureName, nullptr, &_pMainTexture);
	if (FAILED(hr))
	{
		return hr;
	}

	// Load the normal texture if it is provided
	if (normalTextureName != nullptr && hasKnownTextureType(L".dds"))
	{
		hr = CreateDDSTextureFromFile(pD3DDevice, normalTextureName, nullptr, &_pNormalTexture);
		if (FAILED(hr))
		{
			return hr;
		}
	}

	// Create the main sampler state
	D3D11_SAMPLER_DESC mainSamplerDesc = {};
	mainSamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	mainSamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	mainSamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	mainSamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;

	hr = pD3DDevice->CreateSamplerState(&mainSamplerDesc, &_pMainSampler);
	if (FAILED(hr))
	{
		return hr;
	}

	// Create the normal sampler state if the normal texture is provided
	if (_pNormalTexture != nullptr)
	{
		D3D11_SAMPLER_DESC normalSamplerDesc = {};
		normalSamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		normalSamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		normalSamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		normalSamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;

		hr = pD3DDevice->CreateSamplerState(&normalSamplerDesc, &_pNormalSampler);
		if (FAILED(hr))
		{
			return hr;
		}
	}

	return S_OK;
}
	