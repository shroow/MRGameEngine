#include "shrMonsterScript.h"
#include "shrGameObject.h"
#include "shrTransform.h"
#include "shrTime.h"
#include "shrInput.h"
#include "shrSpriteRenderer.h"
#include "shrFadeInScript.h"
#include "shrResources.h"
#include "shrAnimator.h"

namespace shr
{
	MonsterScript::MonsterScript()
		: Script()
		, mOwnerTR(nullptr)
		, mIdle(false)
		, mDie(false)
		, mAttack(false)
		, mChange(false)
		, mStatus{}
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
		mAnimator = GetOwner()->GetComponent<Animator>();

		mStatus.maxHP = 100.f;
		mStatus.HP = mStatus.maxHP;
		mStatus.maxMP = 100.f;
		mStatus.MP = mStatus.maxHP;

		mStatus.attackDmg = 10.f;
		mStatus.attackSpeed = 1.f;

		mStatus.moveSpeed = 10.f;
		mStatus.moveType = eMoveType::Ground;

		mIdle = true;

		mAnimator->Play(L"BallandChainBot_Attack");
	}

	void MonsterScript::Update()
	{
		if (mOwnerTR == nullptr)		
		{
			mOwnerTR = GetOwner()->GetComponent<Transform>();
			if (mOwnerTR == nullptr)
				return;
		}
		
		Vector3 pos = mOwnerTR->GetPosition();

		if (Input::GetKeyState(eKeyCode::T) == eKeyState::PRESSED)
		{
			Vector3 rot = mOwnerTR->GetRotation();
			rot.z += 10.0f * Time::DeltaTime();
			mOwnerTR->SetRotation(rot);
		}

		if (Input::GetKeyState(eKeyCode::DOWN) == eKeyState::PRESSED)
		{
			pos.y += -mOwnerTR->Up().y * mStatus.moveSpeed * Time::DeltaTime();
			mOwnerTR->SetPosition(pos);
		}

		if (Input::GetKeyState(eKeyCode::UP) == eKeyState::PRESSED)
		{
			pos.y += mOwnerTR->Up().y * mStatus.moveSpeed * Time::DeltaTime();
			mOwnerTR->SetPosition(pos);
		}

		if (Input::GetKeyState(eKeyCode::LEFT) == eKeyState::PRESSED)
		{
			pos.x += -mOwnerTR->Right().x * mStatus.moveSpeed * Time::DeltaTime();
			mOwnerTR->SetPosition(pos);
		}

		if (Input::GetKeyState(eKeyCode::RIGHT) == eKeyState::PRESSED)
		{
			pos.x += mOwnerTR->Right().x * mStatus.moveSpeed * Time::DeltaTime();
			mOwnerTR->SetPosition(pos);
		}


		if (mStatus.HP <= 0.f)
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
		mStatus.HP -= 30.f * Time::DeltaTime();
	}
	void MonsterScript::OnCollisionExit(Collider2D* collider)
	{
		if (mDie)
			return;

		if (!mIdle)
		{
			//mIdle = true;
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