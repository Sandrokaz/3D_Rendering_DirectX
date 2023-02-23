#include "Material.h"
#include "WICTextureLoader.h"
#include "Utilities.h"
#include <d3dcompiler.h>

#pragma comment(lib, "d3dcompiler.lib")



INT Material::init(ID3D11Device* pD3DDevice, LPCWSTR textureName, LPCWSTR vertexFilePath, LPCWSTR pixelFilePath)
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

	error = createTextureAndSampler( pD3DDevice, textureName);
	CheckError(error);
	



	IsInitialized = TRUE;

	return 0;
}

void Material::render(ID3D11DeviceContext* pD3DDeviceContext)
{
	// set texture and sampler state
	pD3DDeviceContext->PSSetShaderResources(0, 1, &_pTexture);
	pD3DDeviceContext->PSSetSamplers(0, 1, &_pSamplerState);


	// need to add another tex and sampler

	// set shader pipeline
	pD3DDeviceContext->VSSetShader(_pVertexShader, nullptr, 0);
	pD3DDeviceContext->PSSetShader(_pPixelShader, nullptr, 0);
	pD3DDeviceContext->IASetInputLayout(_pInputLayout);

	
}
void Material::deInit()
{
	IsInitialized = FALSE;
	safeRelease<ID3D11ShaderResourceView>(_pTexture);
	safeRelease<ID3D11SamplerState>(_pSamplerState);
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
		XMMATRIX wvpMatrix = worldMatrix * viewMatrix * projectionMatrix; // transpose because of column mayor - row mayor probl took out trasnpoze

		//if (FAILED(hr)) return;

		// Setup  Matrix Buffer Params
		MatrixBuffer* pMatrixBuffer = reinterpret_cast<MatrixBuffer*>(data.pData);	    // changing static cast to reinterpret
		XMStoreFloat4x4(&(pMatrixBuffer->worldViewProjectionMatrix), wvpMatrix);
		XMStoreFloat4x4(&(pMatrixBuffer->worldMatrix), XMMatrixTranspose(worldMatrix));

		pD3DDeviceContext->Unmap(_pMatrixBuffer, 0);

		pD3DDeviceContext->VSSetConstantBuffers(0, 1, &_pMatrixBuffer);				// and this as well 



		// Setup Camera Buffer Params
		hr = pD3DDeviceContext->Map(_pCameraBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
		CheckFailed(hr, 58);


		CameraBuffer* cameraBuffer = reinterpret_cast<CameraBuffer*>(data.pData);
		cameraBuffer->cameraPosition = pCameraPos;
		cameraBuffer->pad = 0;
	
		pD3DDeviceContext->Unmap(_pCameraBuffer, 0);
		bufferNum = 1;
		pD3DDeviceContext->VSSetConstantBuffers(bufferNum, 1, &_pCameraBuffer); // I can move it in render method 




		//return 0;
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
	//return 0;
}





INT Material::createVertexShader(ID3D11Device* pD3DDevice, LPCWSTR vertexFilePath)
{
	ID3DBlob* pCompiledShaderCode = nullptr;

	// load already compiled shader from filepath
	HRESULT hr = D3DReadFileToBlob(vertexFilePath, &pCompiledShaderCode);
	CheckFailed(hr, 62);
	
	// create shader object
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
	//HRESULT hr = D3DReadFileToBlob(TEXT("ColorPixelShader.cso"), &pCompiledShaderCode)
	CheckFailed(hr, 66);

	hr = pD3DDevice->CreatePixelShader(pCompiledShaderCode->GetBufferPointer(), pCompiledShaderCode->GetBufferSize(), nullptr, &_pPixelShader);
	CheckFailed(hr, 68);

	safeRelease<ID3DBlob>(pCompiledShaderCode);

	return 0;
}

INT Material::createInputLayout(ID3D11Device* pD3DDevice, ID3DBlob* pVertexShaderData)
{

	D3D11_INPUT_ELEMENT_DESC elements[3] = {};
	
	// position
	elements[0].SemanticName = "POSITION";
	elements[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	
	// uv
	elements[1].SemanticName = "TEXCOORD";
	elements[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	elements[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

	// normal
	elements[2].SemanticName = "NORMAL";
	elements[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	elements[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
								
	
	//// color
	//elements[3].SemanticName = "COLOR";
	//elements[3].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	//elements[3].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;



	HRESULT hr = pD3DDevice->CreateInputLayout(elements, 3, pVertexShaderData->GetBufferPointer(), pVertexShaderData->GetBufferSize(), &_pInputLayout);
	CheckFailed(hr, 70);
		
		return 0;

}

INT Material::createMatrixBuffer(ID3D11Device* pD3DDevice)
{
	D3D11_BUFFER_DESC desc = {};
	desc.ByteWidth = sizeof(MatrixBuffer);
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.Usage = D3D11_USAGE_DYNAMIC;  // or default
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	// or 0
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;
	

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



INT Material::createTextureAndSampler(ID3D11Device* pD3DDevice, LPCTSTR textureName)
{
	// create texture
	HRESULT hr = CreateWICTextureFromFile(pD3DDevice, textureName, nullptr, &_pTexture);
	CheckFailed(hr, 78);

	// create sampler state
	D3D11_SAMPLER_DESC desc = {};
	desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	

	hr = pD3DDevice->CreateSamplerState(&desc, &_pSamplerState);
	CheckFailed(hr,80);
	
	return 0;
}
