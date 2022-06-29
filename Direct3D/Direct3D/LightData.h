#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

class Light
{
public:

	struct LightData
	{
	
		XMFLOAT3 lightPosition;
		FLOAT lightIntensity;

		XMFLOAT4 lightDiffuseColor;
		XMFLOAT4 lightAmbientColor;

		XMFLOAT3 lightDirection;
		FLOAT specularPower;

		XMFLOAT4 specularColor;
		FLOAT type;
		XMFLOAT3 padding;
	
	};

	INT Initialize(ID3D11Device* pD3DDevice, LightData &light, INT id = 0);
	void Render(ID3D11DeviceContext* pD3DDeviceContext);
	void DeInitialize();

private:
	INT _id = 0; // light slot
	LightData _light = {}; // light information
	ID3D11Buffer* _pLightBuffer = nullptr;
};

