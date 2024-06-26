#include "Camera.h";

Camera::Camera()
{
	// Set Position
	_positionFloat3 = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_positionVector = XMLoadFloat3(&_positionFloat3);

	// Set Rotation
	_rotationFloat3 = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_rotationVector = XMLoadFloat3(&_rotationFloat3);

	updateViewMatrix();
}

void Camera::setProjectionValues(FLOAT _fovDegrees, INT _screenWidth, INT _screenHeight, FLOAT _nearZ, FLOAT _farZ)
{
	// Convert FOV from degrees to Radians
	FLOAT fovRadians = (_fovDegrees / 360.0f) * XM_2PI;

	// Calculate Aspect Ratio
	FLOAT aspectRatio = static_cast<FLOAT>(_screenWidth) / static_cast<FLOAT>(_screenHeight);

	// Create Projection Matrix
	_projectionMatrix = XMMatrixPerspectiveFovLH(fovRadians, aspectRatio, _nearZ, _farZ);
	updateViewMatrix();
}

void Camera::update(FLOAT t_deltaTime)
{
	float move = 5.0f * t_deltaTime;			// Move Speed
	float camSpeed = 2.0f * t_deltaTime;		// Rotation Sensitivity

	// Move Camera using WASD
	if (GetAsyncKeyState('W') & 0x8000) adjustPosition(getForwardVector() * move);		// Move Forward
	if (GetAsyncKeyState('A') & 0x8000) adjustPosition(getleftVector() * move);			// Move Left
	if (GetAsyncKeyState('S') & 0x8000) adjustPosition(getBackwardVector() * move);		// Move Backwards
	if (GetAsyncKeyState('D') & 0x8000) adjustPosition(getRightVector() * move);		// Move Right

	// Move Camera Up and Down using Q and E
	if (GetAsyncKeyState('E') & 0x8000) adjustPosition(0.0f, move, 0.0f);				// Move Up
	if (GetAsyncKeyState('Q') & 0x8000) adjustPosition(0.0f, -move, 0.0f);				// Move Down

	// Rotate Camera using Arrow keys
	if (GetAsyncKeyState(VK_UP) & 0x8000) adjustRotation(-camSpeed, 0.0f, 0.0f);		// Look Up
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) adjustRotation(camSpeed, 0.0f, 0.0f);		// Look Down
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) adjustRotation(0.0f, -camSpeed, 0.0f);		// Turn Left
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) adjustRotation(0.0f, camSpeed, 0.0f);		// Turn Right
}

void Camera::deInit()
{
}

const XMMATRIX& Camera::getViewMatrix() const
{
	return _viewMatrix;
}

const XMFLOAT4X4 Camera::getViewMatrix4x4()
{
	XMStoreFloat4x4(&_viewMatrix4x4, _viewMatrix);
	return _viewMatrix4x4;
}

const XMMATRIX& Camera::getProjectionMatrix() const
{
	return _projectionMatrix;
}

const XMFLOAT4X4 Camera::getProjectionMatrix4x4()
{
	XMStoreFloat4x4(&_projectionMatrix4x4, _projectionMatrix);
	return _projectionMatrix4x4;
}

const XMVECTOR& Camera::getPositionVector() const
{
	return _positionVector;
}

const XMFLOAT3& Camera::getPositionFloat3() const
{
	return _positionFloat3;
}

const XMVECTOR& Camera::getRotationVector() const
{
	return _rotationVector;
}

const XMFLOAT3& Camera::getRotationFloat3() const
{
	return _rotationFloat3;
}

void Camera::setPosition(const XMVECTOR& pos)
{
	XMStoreFloat3(&_positionFloat3, pos);
	_positionVector = pos;
	updateViewMatrix();
}

void Camera::setPosition(FLOAT x, FLOAT y, FLOAT z)
{
	_positionFloat3 = XMFLOAT3(x, y, z);
	_positionVector = XMLoadFloat3(&_positionFloat3);
	updateViewMatrix();
}

void Camera::adjustPosition(const XMVECTOR& pos)
{
	_positionVector += pos;
	XMStoreFloat3(&_positionFloat3, _positionVector);
	updateViewMatrix();
}

void Camera::adjustPosition(FLOAT x, FLOAT y, FLOAT z)
{
	_positionFloat3.x += x;
	_positionFloat3.y += y;
	_positionFloat3.z += z;

	_positionVector = XMLoadFloat3(&_positionFloat3);
	updateViewMatrix();
}

void Camera::setRotation(const XMVECTOR& rot)
{
	_rotationVector = rot;
	XMStoreFloat3(&_rotationFloat3, _rotationVector);
	updateViewMatrix();
}

void Camera::setRotation(FLOAT x, FLOAT y, FLOAT z)
{
	_rotationFloat3 = XMFLOAT3(x, y, z);
	_rotationVector = XMLoadFloat3(&_rotationFloat3);
	updateViewMatrix();
}

void Camera::adjustRotation(const XMVECTOR& rot)
{
	_rotationVector += rot;
	XMStoreFloat3(&_rotationFloat3, _rotationVector);
	updateViewMatrix();
}

void Camera::adjustRotation(FLOAT x, FLOAT y, FLOAT z)
{
	_rotationFloat3.x += x;
	_rotationFloat3.y += y;
	_rotationFloat3.z += z;

	_rotationVector = XMLoadFloat3(&_rotationFloat3);
	updateViewMatrix();
}

void Camera::setLookAtPos(XMFLOAT3 lookAtPos)
{
	if (lookAtPos.x == _positionFloat3.x && lookAtPos.y == _positionFloat3.y && lookAtPos.z == _positionFloat3.z)
		return;

	lookAtPos.x = _positionFloat3.x - lookAtPos.x;
	lookAtPos.y = _positionFloat3.y - lookAtPos.y;
	lookAtPos.z = _positionFloat3.z - lookAtPos.z;

	// Calculate Pitch
	float pitch = 0.0f;
	if (lookAtPos.y != 0.0f)
	{
		const float dist = sqrt(lookAtPos.x * lookAtPos.x + lookAtPos.z * lookAtPos.z);
		pitch = atan(lookAtPos.y / dist);
	}

	// Calculate YAW
	float yaw = 0.0f;
	if (lookAtPos.x != 0.0f)
		yaw = atan(lookAtPos.x / lookAtPos.z);

	if (lookAtPos.z > 0)
		yaw += XM_PI;

	setRotation(pitch, yaw, 0.0f);
}

const XMVECTOR& Camera::getForwardVector()
{
	return _forwardVector;
}

const XMVECTOR& Camera::getBackwardVector()
{
	return _backwardVector;
}

const XMVECTOR& Camera::getleftVector()
{
	return _leftVector;
}

const XMVECTOR& Camera::getRightVector()
{
	return _rightVector;
}

void Camera::updateViewMatrix()
{
	// Calculate Rotation Matrix
	XMMATRIX camRotMatrix = XMMatrixRotationRollPitchYaw(_rotationFloat3.x, _rotationFloat3.y, _rotationFloat3.z);

	// Calculate Camera Target
	XMVECTOR camTarget = XMVector3TransformCoord(DEFAULT_FORWARD_VECTOR, camRotMatrix);

	// Offset camera to camera's current position
	camTarget += _positionVector;

	// Calculate Up Direction
	XMVECTOR upDirection = XMVector3TransformCoord(DEFAULT_UP_VECTOR, camRotMatrix);

	// Rebuild
	_viewMatrix = XMMatrixLookAtLH(_positionVector, camTarget, upDirection);


	XMMATRIX rotMatrix = XMMatrixRotationRollPitchYaw(_rotationFloat3.x, _rotationFloat3.y, 0.0f);

	_forwardVector = XMVector3TransformCoord(DEFAULT_FORWARD_VECTOR, rotMatrix);
	_backwardVector = XMVector3TransformCoord(DEFAULT_BACKWARD_VECTOR, rotMatrix);
	_leftVector = XMVector3TransformCoord(DEFAULT_LEFT_VECTOR, rotMatrix);
	_rightVector = XMVector3TransformCoord(DEFAULT_RIGHT_VECTOR, rotMatrix);
}



