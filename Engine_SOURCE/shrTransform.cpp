#include "shrTransform.h"
#include "shrRenderer.h"
#include "shrCamera.h"

namespace shr
{
	Transform::Transform()
		: Component(eComponentType::Transform)
		, mParent(nullptr)
		, mFoward(Vector3::Forward)
		, mRight(Vector3::Right)
		, mUp(Vector3::Up)
		, mPosition(Vector3::One)
		, mRotation(Vector3::Zero)
		, mScale(Vector3::One)
	{
	}

	Transform::~Transform()
	{
	}

	void Transform::Initialize()
	{
	}

	void Transform::Update()
	{
		//실제 로직상 캐릭터 이동
	}

	void Transform::FixedUpdate()
	{
		//렌더링에 사용될 위치값들을 업데이트

		// 월드 행렬 생성

		// 크기 변환 행렬
		Matrix scale = Matrix::CreateScale(mScale);

		// 회전 변환 행렬
		Matrix rotation;
		rotation = Matrix::CreateRotationX(mRotation.x);
		rotation *= Matrix::CreateRotationY(mRotation.y);
		rotation *= Matrix::CreateRotationZ(mRotation.z);

		// 이동 변환 행렬
		Matrix position;
		position.Translation(mPosition);

		mWorld = scale * rotation * position;

		mFoward = Vector3::TransformNormal(Vector3::Forward, rotation);
		mRight = Vector3::TransformNormal(Vector3::Right, rotation);
		mUp = Vector3::TransformNormal(Vector3::Up, rotation);

		// 카메라 컴포넌트에서 세팅해준다
		// 뷰행렬 세팅
		// 프로젝션 행렬 세팅

		if (mParent)
		{
			mWorld *= mParent->mWorld;
		}
	}

	void Transform::Render()
	{
	}

	void Transform::SetConstantBuffer()
	{
		//ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Transform];
		//
		//Vector4 pos(mPosition.x, mPosition.y, mPosition.z, 0.0f);
		//cb->Bind(&pos);
		renderer::TransformCB trCb = {};
		trCb.world = mWorld;
		trCb.view = Camera::GetGPUViewMatrix();
		trCb.projection = Camera::GetGPUProjectionMatrix();

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Transform];
		cb->SetData(&trCb);
		cb->Bind(eShaderStage::VS);
	}
}
