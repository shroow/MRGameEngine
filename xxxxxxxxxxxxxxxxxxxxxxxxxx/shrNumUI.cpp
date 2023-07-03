#include "shrNumUI.h"
#include "shrSpriteRenderer.h"
#include "shrResources.h"
#include "shrTexture.h"
#include "shrObject.h"

namespace shr
{
	NumUI::NumUI()
		: GameObject()
		, mNum(0)
		, mSprite0(nullptr)
		, mSprite10(nullptr)
	{
	}
	NumUI::NumUI(const NumUI& obj)
		: mNum(obj.mNum)
		, mSprite0(nullptr)
		, mSprite10(nullptr)
	{
	}
	NumUI::~NumUI()
	{
	}
	void NumUI::Initialize()
	{
		//0
		{
			Transform* tr = GetComponent<Transform>();

			mSprite0 = object::Instantiate<GameObject>(eLayerType::SystemUI);
			mSprite0->SetName(L"Num0");
			Transform* objTR = mSprite0->GetComponent<Transform>();
			objTR->SetParent(tr);

			std::wstring materialName = L"Material_Num_";
			std::wstringstream ss;
			UINT num = mNum % 10;
			ss << num;
			materialName += ss.str();

			SpriteRenderer* sr = mSprite0->AddComponent<SpriteRenderer>();
			std::shared_ptr <Material> mr = Resources::Find<Material>(materialName);
			std::shared_ptr <Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			sr->SetMaterial(mr);
			sr->SetMesh(mesh);
		}
		//10
		{
			Transform* tr = GetComponent<Transform>();

			mSprite10 = object::Instantiate<GameObject>(eLayerType::SystemUI);
			mSprite10->SetName(L"Num10");
			Transform* objTR = mSprite10->GetComponent<Transform>();
			objTR->SetParent(tr);
			objTR->SetPosition(Vector3(-0.5f, 1.f, 1.f));

			std::wstring materialName = L"Material_Num_";
			std::wstringstream ss;
			UINT num = mNum / 10;
			ss << num;
			materialName += ss.str();

			SpriteRenderer* sr = mSprite10->AddComponent<SpriteRenderer>();
			std::shared_ptr <Material> mr = Resources::Find<Material>(materialName);
			std::shared_ptr <Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			sr->SetMaterial(mr);
			sr->SetMesh(mesh);
		}
	}
	void NumUI::Update()
	{
		GameObject::Update();

		//0
		{
			std::wstring materialName = L"Material_Num_";
			std::wstringstream ss;
			UINT num = mNum % 10;
			ss << num;
			materialName += ss.str();

			SpriteRenderer* sr = mSprite0->GetComponent<SpriteRenderer>();
			std::shared_ptr <Material> mr = Resources::Find<Material>(materialName);
			sr->SetMaterial(mr);
		}
		//10
		{
			std::wstring materialName = L"Material_Num_";
			std::wstringstream ss;
			UINT num = mNum / 10;
			ss << num;
			materialName += ss.str();

			SpriteRenderer* sr = mSprite10->GetComponent<SpriteRenderer>();
			std::shared_ptr <Material> mr = Resources::Find<Material>(materialName);
			sr->SetMaterial(mr);
		}
	}
	void NumUI::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void NumUI::Render()
	{
		GameObject::Render();
	}
}
