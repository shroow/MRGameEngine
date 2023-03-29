#pragma once
#include <DirectXMath.h>

using namespace DirectX;

// 뷰-프로젝션-월드 변환행렬을 계산하는 함수
XMFLOAT4X4 ComputeTransformMatrix(float screenWidth, float screenHeight, float fovAngleY,
	float near, float far, XMFLOAT3 eye, XMFLOAT3 at, XMFLOAT3 up)
{
	// 뷰 매트릭스
	XMMATRIX view = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&at), XMLoadFloat3(&up));

	//scss		Copy code
	
		// 프로젝션 매트릭스
		float aspectRatio = screenWidth / screenHeight;
	XMMATRIX projection = XMMatrixPerspectiveFovLH(fovAngleY, aspectRatio, near, far);

	// 뷰-프로젝션 매트릭스
	XMMATRIX viewProjection = view * projection;

	// 월드 매트릭스
	XMMATRIX world = XMMatrixIdentity();

	// 뷰-프로젝션-월드 변환행렬
	XMFLOAT4X4 transform;
	XMStoreFloat4x4(&transform, world * viewProjection);

	return transform;
}

void MoveObjectOnMouseDown(XMFLOAT2 mousePos, float screenWidth, float screenHeight,
	float fovAngleY, float near, float far, XMFLOAT3 eye, XMFLOAT3 at, XMFLOAT3 up,
	XMFLOAT4X4 worldMatrix)
{
	// 마우스 위치를 뷰포트크기로 정규화
	float x = (mousePos.x / screenWidth) * 2.0f - 1.0f;
	float y = ((screenHeight - mousePos.y) / screenHeight) * 2.0f - 1.0f;

	//scss		Copy code

		// 뷰-프로젝션-월드 변환행렬을 계산
		XMFLOAT4X4 transform = ComputeTransformMatrix(screenWidth, screenHeight, fovAngleY, near, far, eye, at, up);

	// 마우스 위치를 월드좌표계로 변환
	XMFLOAT3 mousePosWorld;
	mousePosWorld.x = x * transform._11 + y * transform._21 + transform._31 + transform._41;
	mousePosWorld.y = x * transform._12 + y * transform._22 + transform._32 + transform._42;
	mousePosWorld.z = x * transform._13 + y * transform._23 + transform._33 + transform._43;

	// 마우스 위치로부터 물체를 선택
	// 여기에서는 코드를 생략합니다.

	// 선택한 물체를 이동시킴
	// 여기에서는 예시로 선택한 물체의 worldMatrix의 위치를 마우스 위치로 변경하는 코드입니다.
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
	// 마우스 위치를 스크린 좌표계에서 NDC 좌표계로 변환합니다.
	float x = (2.0f * mouseX) / screenWidth - 1.0f;
	float y = 1.0f - (2.0f * mouseY) / screenHeight;

	// NDC 좌표계에서 카메라뷰 좌표계로 변환합니다.
	XMMATRIX invViewProj = XMMatrixInverse(nullptr, viewProjMatrix);
	XMVECTOR rayOrigin = XMVectorSet(x, y, 0.0f, 1.0f);
	XMVECTOR rayDir = XMVectorSet(x, y, 1.0f, 1.0f);
	rayOrigin = XMVector3TransformCoord(rayOrigin, invViewProj);
	rayDir = XMVector3TransformNormal(rayDir, invViewProj);

	// 카메라뷰 좌표계에서 월드 좌표계로 변환합니다.
	XMMATRIX invWorld = XMMatrixInverse(nullptr, worldMatrix);
	rayOrigin = XMVector3TransformCoord(rayOrigin, invWorld);
	rayDir = XMVector3TransformNormal(rayDir, invWorld);
}