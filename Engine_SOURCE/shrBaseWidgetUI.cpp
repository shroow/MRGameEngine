#include "shrBaseWidgetUI.h"
#include "shrMesh.h"
#include "shrMaterial.h"
#include "shrUIBase.h"
#include "shrResources.h"
#include "shrSpriteRenderer.h"

namespace shr
{
	BaseWidgetUI::BaseWidgetUI()
		: GameObject()
		, mWidgetSize(Vector2::One)
		, mUIs{}
	{
		mWidgetRenderer = AddComponent<SpriteRenderer>();
	}
	BaseWidgetUI::BaseWidgetUI(const BaseWidgetUI& obj)
		: GameObject(obj)
		, mWidgetSize(obj.mWidgetSize)
		, mUIs{}
	{
		mWidgetRenderer = AddComponent<SpriteRenderer>();
		//UIs Check how to transform UI info
	}
	BaseWidgetUI::~BaseWidgetUI()
	{
	}

	void BaseWidgetUI::Initialize()
	{
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> mr = Resources::Find<Material>(L"WidgetHorizontal_Material");

		mWidgetRenderer->SetMesh(mesh);
		mWidgetRenderer->SetMaterial(mr);
	}
	void BaseWidgetUI::Update()
	{
		GameObject::Update();
	}
	void BaseWidgetUI::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void BaseWidgetUI::Render()
	{
		GameObject::Render();
	}

	bool BaseWidgetUI::AddUI(GameObject* obj, Vector3 pos)
	{
		if(obj == nullptr)
			return false;

		Transform* tr = GetComponent<Transform>();
		Transform* childtr = obj->GetComponent<Transform>();

		childtr->SetParent(tr);
		childtr->SetPosition(pos);

		mUIs.push_back(obj);

		return true;
	}
}
