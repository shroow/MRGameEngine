#include "shrUnitObject.h"
#include "shrObject.h"
#include "shrSpriteRenderer.h"

namespace shr
{
	UnitObject::UnitObject()
		: GameObject()
		, mBattleBody(nullptr)
		, mCharUI(nullptr)
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

			SpriteRenderer* mr = AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"SpriteMaterial");
			mr->SetMaterial(mateiral);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
		}


		//BattleBody
		{
			mBattleBody = object::Instantiate<GameObject>(eLayerType::Monster);
			Transform* tr = mBattleBody->GetComponent<Transform>();
			Collider2D* collider2 = mBattleBody->AddComponent<Collider2D>();
			collider2->SetType(eColliderType::Circle);
			collider2->SetRadius(20.f); //고정크기 
		}


		//CharUI
		{
			mCharUI = object::Instantiate<GameObject>(eLayerType::Monster);
			Transform* tr = mCharUI->GetComponent<Transform>();
			tr->SetScale(Vector3(6.f, 6.f, 6.f));

			// HPBAR
			GameObject* hpBar = object::Instantiate<GameObject>(eLayerType::Monster);
			hpBar->SetName(L"HPBAR");
			Transform* hpBarTR = hpBar->GetComponent<Transform>();
			hpBarTR->SetParent(tr);
			hpBarTR->SetPosition(Vector3(0.0f, -0.60f, 0.0f));
			hpBarTR->SetScale(Vector3(0.75f, 0.14f, 1.0f));

			SpriteRenderer* hpsr = hpBar->AddComponent<SpriteRenderer>();
			hpBar->AddComponent(hpsr);
			std::shared_ptr<Mesh> hpmesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> hpspriteMaterial = std::make_shared<Material>();
			std::shared_ptr<Texture> hpTex = Resources::Find<Texture>(L"RedBarTexture");
			std::shared_ptr<Shader> hpShader = Resources::Find<Shader>(L"UIShader");
			hpspriteMaterial->SetTexture(eTextureSlot::T0, hpTex);
			hpspriteMaterial->SetShader(hpShader);
			hpsr->SetMesh(hpmesh);
			hpsr->SetMaterial(hpspriteMaterial);

			// MPBAR
			GameObject* mpBar = object::Instantiate<GameObject>(eLayerType::Monster);
			mpBar->SetName(L"MPBAR");
			Transform* mpBarTR = mpBar->GetComponent<Transform>();
			mpBarTR->SetParent(tr);
			mpBarTR->SetPosition(Vector3(0.0f, -0.75f, 0.0f));
			mpBarTR->SetScale(Vector3(0.75f, 0.14f, 1.0f));

			SpriteRenderer* mpSR = mpBar->AddComponent<SpriteRenderer>();
			mpBar->AddComponent(mpSR);
			std::shared_ptr<Mesh> mpMesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> mpSpriteMaterial = std::make_shared<Material>();;
			std::shared_ptr<Texture> mpTex = Resources::Find<Texture>(L"BlueBarTexture");
			std::shared_ptr<Shader> mpShader = Resources::Find<Shader>(L"UIShader");
			mpSpriteMaterial->SetTexture(eTextureSlot::T0, mpTex);
			mpSpriteMaterial->SetShader(mpShader);
			mpSR->SetMesh(mpMesh);
			mpSR->SetMaterial(mpSpriteMaterial);
		}
	}

	void UnitObject::Update()
	{
		GameObject::Update();
	}

	void UnitObject::FixedUpdate()
	{
		GameObject::FixedUpdate();

		Vector3 pos = GetComponent<Transform>()->GetPosition();

		mBattleBody->GetComponent<Transform>()->SetPosition(pos);

		mCharUI->GetComponent<Transform>()->SetPosition(pos);
	}

	void UnitObject::Render()
	{
		GameObject::Render();
	}
	void UnitObject::SetAttackRange(float radius)
	{
	}
}