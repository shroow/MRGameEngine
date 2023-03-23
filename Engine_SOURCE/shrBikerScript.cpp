#include "shrBikerScript.h"
#include "shrGameObject.h"
#include "shrTransform.h"
#include "shrTime.h"
#include "shrInput.h"
#include "shrSpriteRenderer.h"
#include "shrFadeInScript.h"
#include "shrResources.h"
#include "shrAnimator.h"
#include <functional>
#include "shrApplication.h"


extern shr::Application application;
namespace shr
{
	BikerScript::BikerScript()
		: Script(eScriptType::UnitScript)
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

	BikerScript::~BikerScript()
	{
		mOwnerTR = nullptr;
	}

	void BikerScript::Initialize()
	{
		LoadResources();

		if (GetOwner() == nullptr)
			return;

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

		mAnimator->GetStartEvent(L"FreeKnightv1c1_Run_anim") = std::bind(&BikerScript::Start, this);
		mAnimator->GetCompleteEvent(L"FreeKnightv1c1_Idle_anim") = std::bind(&BikerScript::Action, this);
		mAnimator->GetEndEvent(L"FreeKnightv1c1_Idle_anim") = std::bind(&BikerScript::End, this);
		mAnimator->GetEvent(L"FreeKnightv1c1_Idle_anim", 1) = std::bind(&BikerScript::End, this);
	}

	void BikerScript::Update()
	{
		if (mOwnerTR == nullptr)
		{
			mOwnerTR = GetOwner()->GetComponent<Transform>();
			if (mOwnerTR == nullptr)
				return;
		}

		if (Input::GetKeyState(eKeyCode::T) == eKeyState::PRESSED)
		{
			Vector3 rot = mOwnerTR->GetRotation();
			rot.z += 10.0f * Time::DeltaTime();
			mOwnerTR->SetRotation(rot);
		}

		Vector3 pos = mOwnerTR->GetPosition();

		if (Input::GetKeyState(eKeyCode::RIGHT) == eKeyState::PRESSED)
		{
			pos.x += 3.0f * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::LEFT) == eKeyState::PRESSED)
		{
			pos.x -= 3.0f * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::DOWN) == eKeyState::PRESSED)
		{
			pos.y -= 3.0f * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::UP) == eKeyState::PRESSED)
		{
			pos.y += 3.0f * Time::DeltaTime();
		}

		if (Input::GetMouseLeftPressed())
		{
			Vector2 mouseWorldPos = Input::GetMouseWorldPos();

			Vector2 dir;
			dir.x = mouseWorldPos.x - pos.x;
			dir.y = mouseWorldPos.y - pos.y;
			float length = sqrt(dir.x * dir.x + dir.y * dir.y);
			dir.x /= length;
			dir.y /= length;

			// Move object A towards object B
			pos.x += dir.x * 3.0f * Time::DeltaTime();
			pos.y += dir.y * 3.0f * Time::DeltaTime();

			//Vector2 angle = Vector2::AngleBetweenVectors(myPos, mouseWorldPos);
			//
			//pos.x += 3.0f * cos(angle.x) * Time::DeltaTime();
			//pos.y += 3.0f * sin(angle.x) * Time::DeltaTime();
		}

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

	void BikerScript::FixedUpdate()
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
			mAnimator->Play(L"FreeKnightv1c1_Idle_anim", true);
			mChange = false;
		}
		else if (mAttack)
		{
			mAnimator->Play(L"FreeKnightv1c1_Attack_anim", true);
			mChange = false;
		}
		else if (mRun)
		{
			mAnimator->Play(L"FreeKnightv1c1_Run_anim", true);
			mChange = false;
		}
		else if (mIdle)
		{
			mAnimator->Play(L"FreeKnightv1c1_Idle_anim", true);
			mChange = false;
		}


		Animator* animator = GetOwner()->GetComponent<Animator>();
		if (Input::GetKey(eKeyCode::N_1))
		{
			mAnimator->Play(L"FreeKnightv1c1_Attack_anim");
		}
	}

	void BikerScript::Render()
	{
	}

	void BikerScript::LoadResources()
	{
		
	}

	void BikerScript::OnCollisionEnter(Collider2D* collider)
	{
		if (mDie)
			return;

		if (!mAttack)
		{
			mAttack = true;
			mIdle = false;
			mRun = false;
			mChange = true;
		}
	}
	void BikerScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void BikerScript::OnCollisionExit(Collider2D* collider)
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
	void BikerScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void BikerScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void BikerScript::OnTriggerExit(Collider2D* collider)
	{
	}

	void BikerScript::Start()
	{
	}

	void BikerScript::Action()
	{
	}

	void BikerScript::End()
	{
	}

}