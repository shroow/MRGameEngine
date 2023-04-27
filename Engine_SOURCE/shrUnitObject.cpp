#include "shrUnitObject.h"
#include "shrObject.h"
#include "shrSpriteRenderer.h"
#include "shrCharUIScirpt.h"

namespace shr
{
	UnitObject::UnitObject()
		: GameObject()
		, mCharName()
		, mBattleBody(nullptr)
		, mCharUI(nullptr)
		, mMonScript(nullptr)
		, mUIScript(nullptr)
	{
	}
	UnitObject::UnitObject(const UnitObject& obj)
		: GameObject(obj)
	{
	}
	UnitObject::~UnitObject()
	{
		mBattleBody->Die();
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

			//�νĹ��� �浹ü
			Collider2D* collider2 = new Collider2D(eComponentType::Collider2);
			AddComponent(collider2);
			collider2->SetType(eColliderType::Circle);
			collider2->SetRadius(30.f); //����ũ�� 

			SpriteRenderer* mr = AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"SpriteMaterial");
			mr->SetMaterial(mateiral);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			mMonScript = AddComponent<UnitScript>();
		}

		//BattleBody
		{
			mBattleBody = object::Instantiate<GameObject>(eLayerType::Monster);
			//Transform* tr = mBattleBody->GetComponent<Transform>();
			//Collider2D* collider2 = mBattleBody->AddComponent<Collider2D>();
			//collider2->SetType(eColliderType::Circle);
			//collider2->SetRadius(20.f); //����ũ�� 
		}

		mCharUI = object::Instantiate<GameObject>(eLayerType::Monster);
	}

	void UnitObject::Update()
	{
		GameObject::Update();

		Vector3 pos = GetComponent<Transform>()->GetPosition();

		mBattleBody->GetComponent<Transform>()->SetPosition(pos);

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

	void UnitObject::SetChar(std::wstring name, Vector3 pos)
	{
		mCharName = name;
		mMonScript->SetChar(name);

		GetComponent<Transform>()->SetPosition(pos);
	}

	void UnitObject::SetAttackRange(float radius)
	{
	}
}