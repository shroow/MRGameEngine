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