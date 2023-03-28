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
		//���� ������ ĳ���� �̵�
	}

	void Transform::FixedUpdate()
	{
		//�������� ���� ��ġ������ ������Ʈ

		// ���� ��� ����

		// ũ�� ��ȯ ���
		Matrix scale = Matrix::CreateScale(mScale);

		// ȸ�� ��ȯ ���
		Matrix rotation;
		rotation = Matrix::CreateRotationX(mRotation.x);
		rotation *= Matrix::CreateRotationY(mRotation.y);
		rotation *= Matrix::CreateRotationZ(mRotation.z);

		// �̵� ��ȯ ���
		Matrix position;
		position.Translation(mPosition);

		mWorld = scale * rotation * position;

		mFoward = Vector3::TransformNormal(Vector3::Forward, rotation);
		mRight = Vector3::TransformNormal(Vector3::Right, rotation);
		mUp = Vector3::TransformNormal(Vector3::Up, rotation);

		// ī�޶� ������Ʈ���� �������ش�
		// ����� ����
		// �������� ��� ����

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
