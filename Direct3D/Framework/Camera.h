//#pragma once

#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

class Camera
{
public:
	Camera();

	void setProjectionValues(FLOAT _fovDegrees, INT _screenWidth, INT _screenHeight, FLOAT _nearZ, FLOAT _farZ);
	void update(FLOAT t_deltaTime);
	void deInit();

	const XMMATRIX& getViewMatrix() const;
	const XMFLOAT4X4 getViewMatrix4x4();
	const XMMATRIX& getProjectionMatrix() const;
	const XMFLOAT4X4 getProjectionMatrix4x4();

	const XMVECTOR& getPositionVector() const;
	const XMFLOAT3& getPositionFloat3() const;
	const XMVECTOR& getRotationVector() const;
	const XMFLOAT3& getRotationFloat3() const;

	void setPosition(const XMVECTOR& pos);
	void setPosition(FLOAT x, FLOAT y, FLOAT z);
	void adjustPosition(const XMVECTOR& pos);
	void adjustPosition(FLOAT x, FLOAT y, FLOAT z);
	void setRotation(const XMVECTOR& rot);
	void setRotation(FLOAT x, FLOAT y, FLOAT z);
	void adjustRotation(const XMVECTOR& rot);
	void adjustRotation(FLOAT x, FLOAT y, FLOAT z);
	void setLookAtPos(XMFLOAT3 _lookAtPos);

	const XMVECTOR& getForwardVector();
	const XMVECTOR& getBackwardVector();
	const XMVECTOR& getleftVector();
	const XMVECTOR& getRightVector();

private:
	void updateViewMatrix();

	XMVECTOR _positionVector;
	XMVECTOR _rotationVector;

	XMFLOAT3 _positionFloat3;
	XMFLOAT3 _rotationFloat3;

	XMMATRIX _viewMatrix;
	XMFLOAT4X4 _viewMatrix4x4;
	XMMATRIX _projectionMatrix;
	XMFLOAT4X4 _projectionMatrix4x4;

		const XMVECTOR DEFAULT_FORWARD_VECTOR = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
		const XMVECTOR DEFAULT_BACKWARD_VECTOR = XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f);
		const XMVECTOR DEFAULT_UP_VECTOR = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		const XMVECTOR DEFAULT_LEFT_VECTOR = XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f);
		const XMVECTOR DEFAULT_RIGHT_VECTOR = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

		XMVECTOR _forwardVector;
		XMVECTOR _backwardVector;
		XMVECTOR _leftVector;
		XMVECTOR _rightVector;
};

