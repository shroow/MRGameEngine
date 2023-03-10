#include "shrMonsterScript.h"
#include "shrGameObject.h"
#include "shrTransform.h"
#include "shrTime.h"
#include "shrInput.h"
#include "shrSpriteRenderer.h"
#include "shrFadeInScript.h"
#include "shrResources.h"

namespace shr
{
	MonsterScript::MonsterScript()
		: Script()
		, mOwnerTR(nullptr)
		, mIdle(false)
		, mDie(false)
		, mAttack(false)
		, mChange(false)
		, mHP(0.f)
		, mMaxHP(100.f)
	{
	}

	MonsterScript::~MonsterScript()
	{
		mOwnerTR = nullptr;
	}

	void MonsterScript::Initialize()
	{
		LoadResources();

		mOwnerTR = GetOwner()->GetComponent<Transform>();
		//if(mOwnerTR)
		//	mOwnerTR->SetScale(Vector3(4.0f, 1.0f, 1.0f));

		mIdle = true;
		mHP = mMaxHP;
	}

	void MonsterScript::Update()
	{
		if (Input::GetKeyState(eKeyCode::T) == eKeyState::PRESSED)
		{
			Vector3 rot = mOwnerTR->GetRotation();
			rot.z += 10.0f * Time::DeltaTime();
			mOwnerTR->SetRotation(rot);
		}

		Vector3 pos = mOwnerTR->GetPosition();

		if (mHP <= 0.f)
		{
			mIdle = false;
			mAttack = false;
			mDie = true;
			mChange = true;
		}

		mOwnerTR->SetPosition(pos);
	}

	void MonsterScript::FixedUpdate()
	{
		if (!mChange)
			return;

		if (mIdle)
		{
			std::shared_ptr<Material> material
				= Resources::Find<Material>(L"Monster_Idle_Material");
			if (material == nullptr)
				return;
			GetOwner()->GetComponent<SpriteRenderer>()->SetMaterial(material);

			mChange = false;
		}
		else if (mAttack)
		{
			std::shared_ptr<Material> material
				= Resources::Find<Material>(L"Monster_Attack2_Material");
			if (material == nullptr)
				return;
			GetOwner()->GetComponent<SpriteRenderer>()->SetMaterial(material);

			mChange = false;
		}
		else if (mDie)
		{
			std::shared_ptr<Material> material
				= Resources::Find<Material>(L"Monster_Death_Material");
			if (material == nullptr)
				return;
			GetOwner()->GetComponent<SpriteRenderer>()->SetMaterial(material);

			mChange = false;
		}
	}

	void MonsterScript::Render()
	{
	}

	void MonsterScript::LoadResources()
	{
		
	}

	void MonsterScript::OnCollisionEnter(Collider2D* collider)
	{
		if (mDie)
			return;

		if (!mAttack)
		{
			mAttack = true;
			mIdle = false;
			mChange = true;
		}
	}
	void MonsterScript::OnCollisionStay(Collider2D* collider)
	{
		mHP -= 30.f * Time::DeltaTime();
	}
	void MonsterScript::OnCollisionExit(Collider2D* collider)
	{
		if (mDie)
			return;

		if (!mIdle)
		{
			mIdle = true;
			mAttack = false;
			mChange = true;
		}
	}
	void MonsterScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void MonsterScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void MonsterScript::OnTriggerExit(Collider2D* collider)
	{
	}
}