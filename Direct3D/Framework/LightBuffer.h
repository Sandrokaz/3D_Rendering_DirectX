#pragma once
#include "DirectXMath.h"

using namespace DirectX;

struct LightBuffer
{
	XMFLOAT4 ambientColor;
	XMFLOAT4 diffuseColor;
	XMFLOAT3 lightDirection;
	FLOAT specularPower;
	XMFLOAT4 specularColor;
	FLOAT roughness;
	XMFLOAT3 padding;
	
};


