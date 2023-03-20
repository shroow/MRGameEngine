#pragma once
#include <DirectXMath.h>

using namespace DirectX;

// ��-��������-���� ��ȯ����� ����ϴ� �Լ�
XMFLOAT4X4 ComputeTransformMatrix(float screenWidth, float screenHeight, float fovAngleY,
	float near, float far, XMFLOAT3 eye, XMFLOAT3 at, XMFLOAT3 up)
{
	// �� ��Ʈ����
	XMMATRIX view = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&at), XMLoadFloat3(&up));

	//scss		Copy code
	
		// �������� ��Ʈ����
		float aspectRatio = screenWidth / screenHeight;
	XMMATRIX projection = XMMatrixPerspectiveFovLH(fovAngleY, aspectRatio, near, far);

	// ��-�������� ��Ʈ����
	XMMATRIX viewProjection = view * projection;

	// ���� ��Ʈ����
	XMMATRIX world = XMMatrixIdentity();

	// ��-��������-���� ��ȯ���
	XMFLOAT4X4 transform;
	XMStoreFloat4x4(&transform, world * viewProjection);

	return transform;
}

void MoveObjectOnMouseDown(XMFLOAT2 mousePos, float screenWidth, float screenHeight,
	float fovAngleY, float near, float far, XMFLOAT3 eye, XMFLOAT3 at, XMFLOAT3 up,
	XMFLOAT4X4 worldMatrix)
{
	// ���콺 ��ġ�� ����Ʈũ��� ����ȭ
	float x = (mousePos.x / screenWidth) * 2.0f - 1.0f;
	float y = ((screenHeight - mousePos.y) / screenHeight) * 2.0f - 1.0f;

	//scss		Copy code

		// ��-��������-���� ��ȯ����� ���
		XMFLOAT4X4 transform = ComputeTransformMatrix(screenWidth, screenHeight, fovAngleY, near, far, eye, at, up);

	// ���콺 ��ġ�� ������ǥ��� ��ȯ
	XMFLOAT3 mousePosWorld;
	mousePosWorld.x = x * transform._11 + y * transform._21 + transform._31 + transform._41;
	mousePosWorld.y = x * transform._12 + y * transform._22 + transform._32 + transform._42;
	mousePosWorld.z = x * transform._13 + y * transform._23 + transform._33 + transform._43;

	// ���콺 ��ġ�κ��� ��ü�� ����
	// ���⿡���� �ڵ带 �����մϴ�.

	// ������ ��ü�� �̵���Ŵ
	// ���⿡���� ���÷� ������ ��ü�� worldMatrix�� ��ġ�� ���콺 ��ġ�� �����ϴ� �ڵ��Դϴ�.
	worldMatrix._41 = mousePosWorld.x;
	worldMatrix._42 = mousePosWorld.y;
	worldMatrix._43 = mousePosWorld.z;
}