#include "shrStageIconObject.h"

namespace shr
{
	StageIconObject::StageIconObject()
		: GameObject()
		, mIsSelected(false)
		, mStageNum(Vector2::Zero)
		, mStageDetail(nullptr)
	{
	}
	StageIconObject::~StageIconObject()
	{
	}

	void StageIconObject::Initialize()
	{
	}
	void StageIconObject::Update()
	{
		GameObject::Update();
	}
	void StageIconObject::FixedUpdate()
	{
		GameObject::FixedUpdate();

		if (mIsSelected)
		{
			//go to Selected Stage
		}
	}
	void StageIconObject::Render()
	{
		GameObject::Render();
	}
	void StageIconObject::Die()
	{
		GameObject::Die();
	}
}