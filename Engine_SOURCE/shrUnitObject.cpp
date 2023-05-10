#include "shrUnitObject.h"
#include "shrObject.h"
#include "shrSpriteRenderer.h"
#include "shrUnitScript.h"
#include "shrCharUIScirpt.h"
#include "shrResources.h"
#include "shrAnimator.h"
#include <fstream>
#include <sstream>
#include <locale>
#include "shrUnitUI.h"


namespace shr
{
	UnitObject::UnitObject()
		: GameObject()
		, mUnitStatus()
		, mUnitState()
		, mTrade(false)
		, mCharUI(nullptr)
		, mMonScript(nullptr)
		, mUIScript(nullptr)
		, mOwner(nullptr)
	{
	}
	UnitObject::UnitObject(const UnitObject& obj)
		: GameObject(obj)
		, mUnitStatus(obj.mUnitStatus)
		, mUnitState(obj.mUnitState)
		, mTrade(obj.mTrade)
		, mCharUI(nullptr)
		, mMonScript(nullptr)
		, mUIScript(nullptr)
		, mOwner(obj.mOwner)
	{
	}
	UnitObject::~UnitObject()
	{
		if (mCharUI != nullptr)
			mCharUI->Die();
	}

	void UnitObject::Initialize()
	{
		GameObject::Initialize();

		//Body
		{
			Transform* tr = GetComponent<Transform>();
			Collider2D* collider = AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			collider->SetSize(Vector2(0.5f, 1.0f));

			//인식범위 충돌체
			Collider2D* collider2 = new Collider2D(eComponentType::Collider2);
			AddComponent(collider2);
			collider2->SetType(eColliderType::Circle);
			collider2->SetRadius(10.f); //고정크기 

			SpriteRenderer* mr = AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"SpriteMaterial");
			mr->SetMaterial(mateiral);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			AddComponent<Animator>();
			mMonScript = AddComponent<UnitScript>();
		}

		mCharUI = object::Instantiate<UnitUI>(eLayerType::Monster);
		object::DontDestroyOnLoad(mCharUI);
	}

	void UnitObject::Update()
	{
		GameObject::Update();
	}

	void UnitObject::FixedUpdate()
	{
		GameObject::FixedUpdate();

		Vector3 pos = GetComponent<Transform>()->GetPosition();

		mCharUI->GetComponent<Transform>()->SetPosition(pos);
	}

	void UnitObject::Render()
	{
		GameObject::Render();
	}

	void UnitObject::Die()
	{
		mCharUI->Die();

		mCharUI = nullptr;

		DontDestroy(false);
		GameObject::Die();
	}

	void UnitObject::SetCharType(eUnitType type)
	{
		mUnitStatus.SetUnitType(type);
		mMonScript->SetUnitAnim(type);
	}

	void UnitObject::SetCharType(eUnitType type, Vector3 pos)
	{
		mUnitStatus.SetUnitType(type);
		mMonScript->SetUnitAnim(type);

		GetComponent<Transform>()->SetPosition(pos);
	}

	void UnitObject::SetAttackRange(float radius)
	{
	}

	bool LoadUnitInfo() 
	{
		return false;
	}
}