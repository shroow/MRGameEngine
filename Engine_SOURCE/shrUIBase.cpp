#include "shrUIBase.h"
#include "shrSpriteRenderer.h"
#include "shrCollider2D.h"
#include "shrResources.h"

namespace shr
{
	UIBase::UIBase()
		: GameObject()
		, mbUseUV(false)
		, mStartUV(Vector2::Zero)
		, mEndUV(Vector2::One)
	{
		mUIRenderer = AddComponent<SpriteRenderer>();
	}

	UIBase::UIBase(const UIBase& obj)
		: GameObject(obj)
		, mbUseUV(obj.mbUseUV)
		, mStartUV(obj.mStartUV)
		, mEndUV(obj.mEndUV)
	{
		mUIRenderer = AddComponent<SpriteRenderer>();
	}

	UIBase::~UIBase()
	{
	}

	void UIBase::Initialize()
	{
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> mr = Resources::Find<Material>(L"DefaultUI_Material");

		mUIRenderer->SetMesh(mesh);
		mUIRenderer->SetMaterial(mr);
	}

	void UIBase::Update()
	{
		GameObject::Update();
	}

	void UIBase::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void UIBase::Render()
	{
		std::shared_ptr<Material> mr = mUIRenderer->GetMaterial();

		if (mr != nullptr)
		{
			mr->SetData(eGPUParam::Int_1, &mbUseUV);
			mr->SetData(eGPUParam::Vector2_1, &mStartUV);
			mr->SetData(eGPUParam::Vector2_2, &mEndUV);
		}

		GameObject::Render();
	}
	void UIBase::SetRenderer(SpriteRenderer* renderer)
	{
	}
}