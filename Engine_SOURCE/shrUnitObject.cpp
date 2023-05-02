#include "shrUnitObject.h"
#include "shrObject.h"
#include "shrSpriteRenderer.h"
#include "shrCharUIScirpt.h"

namespace shr
{
	UnitObject::UnitObject()
		: GameObject()
		, mUnitStatus()
		, mUnitState()
		, mCharUI(nullptr)
		, mMonScript(nullptr)
		, mUIScript(nullptr)
	{
	}
	UnitObject::UnitObject(const UnitObject& obj)
		: GameObject(obj)
		, mUnitStatus(obj.mUnitStatus)
		, mUnitState(obj.mUnitState)
		, mCharUI(nullptr)
		, mMonScript(nullptr)
		, mUIScript(nullptr)
	{
	}
	UnitObject::~UnitObject()
	{
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

			//인식범위 충돌체
			Collider2D* collider2 = new Collider2D(eComponentType::Collider2);
			AddComponent(collider2);
			collider2->SetType(eColliderType::Circle);
			collider2->SetRadius(30.f); //고정크기 

			SpriteRenderer* mr = AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"SpriteMaterial");
			mr->SetMaterial(mateiral);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			mMonScript = AddComponent<UnitScript>();
		}

		mCharUI = object::Instantiate<GameObject>(eLayerType::Monster);
	}

	void UnitObject::Update()
	{
		GameObject::Update();

		Vector3 pos = GetComponent<Transform>()->GetPosition();

		mCharUI->GetComponent<Transform>()->SetPosition(pos);
	}

	void UnitObject::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void UnitObject::Render()
	{
		GameObject::Render();
	}

	void UnitObject::SetChar(eUnitType type, std::wstring name, Vector3 pos)
	{
		mUnitStatus.SetUnitType(type);
		mUnitStatus.SetCharName(name);

		mMonScript->SetChar(name)

		GetComponent<Transform>()->SetPosition(pos);
	}

	void UnitObject::SetAttackRange(float radius)
	{
	}
}