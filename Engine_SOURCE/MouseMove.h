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

D3DXVECTOR3 ScreenToWorld(D3DXVECTOR3 vScreenPos, D3DXMATRIX matView, D3DXMATRIX matProj, int nScreenWidth, int nScreenHeight)
{
	D3DXVECTOR4 v;
	v.x = (((2.0f * vScreenPos.x) / nScreenWidth) - 1) / matProj._11;
	v.y = -(((2.0f * vScreenPos.y) / nScreenHeight) - 1) / matProj._22;
	v.z = 1.0f;
	v.w = 1.0f;

	D3DXMATRIX m;
	D3DXMatrixInverse(&m, NULL, &matView);

	D3DXVECTOR3 vWorldPos;
	vWorldPos.x = v.x * m._11 + v.y * m._21 + v.z * m._31;
	vWorldPos.y = v.x * m._12 + v.y * m._22 + v.z * m._32;
	vWorldPos.z = v.x * m._13 + v.y * m._23 + v.z * m._33;

	return vWorldPos;
}

void ScreenToWorld()
{
	// ���콺 ��ġ�� ��ũ�� ��ǥ�迡�� NDC ��ǥ��� ��ȯ�մϴ�.
	float x = (2.0f * mouseX) / screenWidth - 1.0f;
	float y = 1.0f - (2.0f * mouseY) / screenHeight;

	// NDC ��ǥ�迡�� ī�޶�� ��ǥ��� ��ȯ�մϴ�.
	XMMATRIX invViewProj = XMMatrixInverse(nullptr, viewProjMatrix);
	XMVECTOR rayOrigin = XMVectorSet(x, y, 0.0f, 1.0f);
	XMVECTOR rayDir = XMVectorSet(x, y, 1.0f, 1.0f);
	rayOrigin = XMVector3TransformCoord(rayOrigin, invViewProj);
	rayDir = XMVector3TransformNormal(rayDir, invViewProj);

	// ī�޶�� ��ǥ�迡�� ���� ��ǥ��� ��ȯ�մϴ�.
	XMMATRIX invWorld = XMMatrixInverse(nullptr, worldMatrix);
	rayOrigin = XMVector3TransformCoord(rayOrigin, invWorld);
	rayDir = XMVector3TransformNormal(rayDir, invWorld);
}