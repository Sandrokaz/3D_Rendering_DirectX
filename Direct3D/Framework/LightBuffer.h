#pragma once
#include "DirectXMath.h"

using namespace DirectX;

struct LightBuffer				  // has to be aligned in 16 byte blocks
{




	XMFLOAT4 ambientColor;
	XMFLOAT4 diffuseColor;
	XMFLOAT3 lightDirection;
	FLOAT specularPower;
	XMFLOAT4 specularColor;	
	FLOAT lightIntensity;
	XMFLOAT4 lightColor;
	FLOAT ambientLightPower;	
	FLOAT glosiness;
	FLOAT padding;
	
	
};


