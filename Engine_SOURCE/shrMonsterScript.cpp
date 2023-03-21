#include "shrMonsterScript.h"
#include "shrGameObject.h"
#include "shrTransform.h"
#include "shrTime.h"
#include "shrInput.h"
#include "shrSpriteRenderer.h"
#include "shrFadeInScript.h"
#include "shrResources.h"
#include "shrAnimator.h"
#include "shrResource.h"

namespace shr
{
	MonsterScript::MonsterScript()
		: Script()
		, mOwnerTR(nullptr)
		, mAnimator(nullptr)
		, mIdle(false)
		, mRun(false)
		, mDie(false)
		, mAttack(false)
		, mChange(false)
		, mPrevPos{}
		, mMove(0.f)
		, mStatus{}
	{
	}

	MonsterScript::~MonsterScript()
	{
		mOwnerTR = nullptr;
	}

	void MonsterScript::Initialize()
	{
		if (mAnimator == nullptr)
			return;
		mAnimator->GetStartEvent(L"Run_Anim") = std::bind(&MonsterScript::Start, this);
		mAnimator->GetCompleteEvent(L"Idle_Anim") = std::bind(&MonsterScript::Action, this);
		mAnimator->GetEndEvent(L"Idle_Anim") = std::bind(&MonsterScript::End, this);
		mAnimator->GetEvent(L"Idle_Anim", 1) = std::bind(&MonsterScript::End, this);
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


		if (mPrevPos != pos)
		{
			mMove = Vector2::Distance(Vector2(mPrevPos.x, mPrevPos.y), Vector2(pos.x, pos.y));

			if (mIdle)
			{
				mIdle = false;
				mRun = true;
				mChange = true;
			}
		}
		else
		{
			mMove = 0.f;

			if (mRun)
			{
				mIdle = true;
				mRun = false;
				mChange = true;
			}
		}

		mPrevPos = pos;

		mOwnerTR->SetPosition(pos);
	}

	void MonsterScript::FixedUpdate()
	{
		if (!mChange)
			return;

		if (mAnimator == nullptr)
			return;

		if (mDie)
		{
			mAnimator->Play(L"Death_Anim");
			mChange = false;
		}
		else if (mAttack)
		{
			mAnimator->Play(L"Attack_Anim");
			mChange = false;
		}
		else if (mMove)
		{
			mAnimator->Play(L"Run_Anim");
			mChange = false;
		}
		else if (mIdle)
		{
			mAnimator->Play(L"Idle_Anim");
			mChange = false;
		}

		Animator* animator = GetOwner()->GetComponent<Animator>();
		if (Input::GetKey(eKeyCode::N_1))
		{
			mAnimator->Play(L"Attack_Anim");
		}
	}

	void MonsterScript::Render()
	{
	}

	void MonsterScript::SetChar(const std::wstring& name, Status status)
	{
		if (GetOwner() == nullptr)
			return;

		mOwnerTR = GetOwner()->GetComponent<Transform>();
		mAnimator = GetOwner()->AddComponent<Animator>();

		mCharName = name;

		mStatus.maxHP = status.maxHP;
		mStatus.HP = status.HP;
		mStatus.maxMP = status.maxMP;
		mStatus.MP = status.MP;

		mStatus.attackDmg = status.attackDmg;
		mStatus.attackSpeed = status.attackSpeed;

		mStatus.moveSpeed = status.moveSpeed;
		mStatus.moveType = status.moveType;

		mIdle = true;
	}

	void MonsterScript::LoadCharAnim(eAnimState animState, Vector2 offset
		, Vector2 leftTop, Vector2 spriteSize
		, UINT spriteLength, float duration, eAtlasType atlasType)
	{
		std::wstring textureName;
		std::wstring animName;

		textureName = mCharName;

		switch (animState)
		{
		case shr::enums::eAnimState::Idle:
			textureName.append(L"_Idle");
			animName = L"Idle_Anim";
			break;
		case shr::enums::eAnimState::Run:
			textureName.append(L"_Run");
			animName = L"Run_Anim";
			break;
		case shr::enums::eAnimState::Attack:
			textureName.append(L"_Attack");
			animName = L"Attack_Anim";
			break;
		case shr::enums::eAnimState::Attack2:
			textureName.append(L"_Attack2");
			animName = L"Attack2_Anim";
			break;
		case shr::enums::eAnimState::Skill:
			textureName.append(L"_Skill");
			animName = L"Skill_Anim";
			break;
		case shr::enums::eAnimState::Skill2:
			textureName.append(L"_Skill2");
			animName = L"Skill2_Anim";
			break;
		case shr::enums::eAnimState::Hit:
			textureName.append(L"_Hit");
			animName = L"Hit_Anim";
			break;
		case shr::enums::eAnimState::Death:
			textureName.append(L"_Death");
			animName = L"Death_Anim";
			break;
		case shr::enums::eAnimState::End:
			return;
		default:
			return;
		}

		bool isSuccess = mAnimator->Create(animName, Resources::Find<Texture>(textureName)
			, leftTop, spriteSize, offset
			, spriteLength, duration, atlasType);
	}

	void MonsterScript::PlayCharAnim(eAnimState animState)
	{
		switch (animState)
		{
		case shr::enums::eAnimState::Idle:
			mAnimator->Play(L"Idle_Anim");
			break;
		case shr::enums::eAnimState::Run:
			mAnimator->Play(L"Run_Anim");
			break;
		case shr::enums::eAnimState::Attack:
			mAnimator->Play(L"Attack_Anim");
			break;
		case shr::enums::eAnimState::Attack2:
			mAnimator->Play(L"Attack2_Anim");
			break;
		case shr::enums::eAnimState::Skill:
			mAnimator->Play(L"Skill_Anim");
			break;
		case shr::enums::eAnimState::Skill2:
			mAnimator->Play(L"Skill2_Anim");
			break;
		case shr::enums::eAnimState::Hit:
			mAnimator->Play(L"Hit_Anim");
			break;
		case shr::enums::eAnimState::Death:
			mAnimator->Play(L"Death_Anim");
			break;
		default:
			break;
		}
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
	void MonsterScript::Start()
	{
	}
	void MonsterScript::Action()
	{
	}
	void MonsterScript::End()
	{
	}
}