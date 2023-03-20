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

		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetStartEvent(L"BallandChainBot_Run_anim") = std::bind(&MonsterScript::Start, this);
		animator->GetCompleteEvent(L"BallandChainBot_Idle_anim") = std::bind(&MonsterScript::Action, this);
		animator->GetEndEvent(L"BallandChainBot_Idle_anim") = std::bind(&MonsterScript::End, this);
		animator->GetEvent(L"BallandChainBot_Idle_anim", 1) = std::bind(&MonsterScript::End, this);
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


		if (mStatus.HP <= 0.f)
		{
			mIdle = false;
			mAttack = false;
			mDie = true;
			mChange = true;
		}

		//if (mPrevPos != pos)
		//{
		//	mMove = Vector2::Distance(Vector2(mPrevPos.x, mPrevPos.y), Vector2(pos.x, pos.y));

		//	mRun = true;
		//	mChange = true;
		//}
		//else
		//{
		//	mChange = false;
		//	mMove = 0.f;
		//}

		//mPrevPos = pos;


		mOwnerTR->SetPosition(pos);
	}

	void MonsterScript::FixedUpdate()
	{
		if (!mChange)
			return;

		if (mAnimator == nullptr)
		{
			mAnimator = GetOwner()->GetComponent<Animator>();
			if (mAnimator == nullptr)
				return;
		}

		if (mDie)
		{
			mAnimator->Play(L"BallandChainBot_Death_anim");
			mChange = false;
		}
		else if (mAttack)
		{
			mAnimator->Play(L"BallandChainBot_Attack_anim");
			mChange = false;
		}
		else if (mMove)
		{
			mAnimator->Play(L"BallandChainBot_Run_anim");
			mChange = false;
		}
		else if (mIdle)
		{
			mAnimator->Play(L"BallandChainBot_Idle_anim");
			mChange = false;
		}

		Animator* animator = GetOwner()->GetComponent<Animator>();
		if (Input::GetKey(eKeyCode::N_1))
		{
			mAnimator->Play(L"BallandChainBot_Attack_anim");
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