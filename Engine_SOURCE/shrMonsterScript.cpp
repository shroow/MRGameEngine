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
		: Script(eScriptType::UnitScript)
		, mAnimator(nullptr)
		, mIdle(false)
		, mRun(false)
		, mDie(false)
		, mAttack(false)
		, mHit(false)
		, mPrevPos{}
		, mMove(0.f)
		, mDir{}
		, mStatus{}
		, mState(eCharState::None)
		, mPrevState(eCharState::None)
	{
	}

	MonsterScript::~MonsterScript()
	{
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
		Transform* tr = GetOwner()->GetComponent<Transform>();

		Vector3 pos = tr->GetPosition();

		if (mbCursorOn)
		{
			if (Input::GetMouseLeftDown())
				mbSelected = true;
		}

		if (mbSelected && !mbCursorOn)
		{

			if (Input::GetMouseLeftDown())
				mbSelected = false;
		}

		if (mbSelected)
		{
			if(Input::GetMouseRightDown() || Input::GetMouseRightPressed())
			{
				mMovetoPos = Input::GetMouseWorldPos();
				mbStartMove = true;
			}
		}

		//if (Input::GetMouseLeftPressed())
		//{
		//	Vector2 mousePos = Input::GetMouseWorldPos();
		//	Vector2 dir;
		//	dir.x = mousePos.x - pos.x;
		//	dir.y = mousePos.y - pos.y;
		//	float length = sqrt(dir.x * dir.x + dir.y * dir.y);
		//	dir.x /= length;
		//	dir.y /= length;

		//	pos.x += dir.x * mStatus.moveSpeed * Time::DeltaTime();
		//	pos.y += dir.y * mStatus.moveSpeed * Time::DeltaTime();
		//}

		if (mbStartMove)
		{
			Vector2 dir;
			float disX = mMovetoPos.x - pos.x;
			float disY = mMovetoPos.y - pos.y;
			float length = sqrt(disX * disX + disY * disY);
			dir.x = disX / length;
			dir.y = disY / length;

			pos.x += dir.x * mStatus.moveSpeed * Time::DeltaTime();
			pos.y += dir.y * mStatus.moveSpeed * Time::DeltaTime();

			mDir = dir;

			if (disX < 0.001f && disX > -0.001f && disY < 0.001f && disY > -0.001f)
			{
				mbStartMove = false;
			}
		}

		if (mPrevPos != pos)
		{
			mMove = Vector2::Distance(Vector2(mPrevPos.x, mPrevPos.y), Vector2(pos.x, pos.y));

			mRun = true;
			mIdle = false;
		}
		else
		{
			mMove = 0.f;

			mIdle = true;
			mRun = false;
		}

		mPrevPos = pos;

		tr->SetPosition(pos);
	}

	void MonsterScript::FixedUpdate()
	{
		if (mStatus.HP == 0.f)
			mDie = true;

		if (mAnimator == nullptr)
			return;

		if (Input::GetKey(eKeyCode::N_1))
		{
			mAnimator->Play(L"Attack_Anim");
		}


		if (!CharStateChanged()) //¾È ¹Ù²î¾úÀ¸¸é ¸ØÃã
			return;

		PlayCharAnim(mState);
		mPrevState = mState;
	}

	void MonsterScript::Render()
	{
	}

	void MonsterScript::OnCollisionEnter(Collider2D* collider)
	{
		eLayerType type = collider->GetOwner()->GetLayerType();
		if(type == eLayerType::Monster || type == eLayerType::Player)
			mAttack = true;
	}
	void MonsterScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void MonsterScript::OnCollisionExit(Collider2D* collider)
	{
		eLayerType type = collider->GetOwner()->GetLayerType();
		if (type == eLayerType::Monster || type == eLayerType::Player)
			mAttack = false;
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
	void MonsterScript::OnMouseCollisionEnter()
	{
		mbCursorOn = true;
	}
	void MonsterScript::OnMouseCollisionStay()
	{
	}
	void MonsterScript::OnMouseCollisionExit()
	{
		mbCursorOn = false;
	}

	bool MonsterScript::CharStateChanged()
	{
		if (mDie)
		{
			mState = eCharState::Death;
		}
		else if (mAttack)
		{
			mState = eCharState::Attack;
		}
		else if (mRun && mMove != 0.f)
		{
			mState = eCharState::Run;
		}
		else if (mIdle)
		{
			mState = eCharState::Idle;
		}

		if (mHit)
		{

		}

		if (mPrevState == mState)
			return false;

		return true;
	}

	void MonsterScript::SetChar(const std::wstring& name, Status status)
	{
		if (GetOwner() == nullptr)
			return;

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

	void MonsterScript::LoadCharAnim(eCharState animState, Vector2 offset
		, Vector2 leftTop, Vector2 spriteSize
		, UINT spriteLength, float duration, eAtlasType atlasType)
	{
		std::wstring textureName;
		std::wstring animName;

		textureName = mCharName;

		switch (animState)
		{
		case shr::enums::eCharState::Idle:
			textureName.append(L"_Idle");
			animName = L"Idle_Anim";
			break;
		case shr::enums::eCharState::Run:
			textureName.append(L"_Run");
			animName = L"Run_Anim";
			break;
		case shr::enums::eCharState::Attack:
			textureName.append(L"_Attack");
			animName = L"Attack_Anim";
			break;
		case shr::enums::eCharState::Attack2:
			textureName.append(L"_Attack2");
			animName = L"Attack2_Anim";
			break;
		case shr::enums::eCharState::Skill:
			textureName.append(L"_Skill");
			animName = L"Skill_Anim";
			break;
		case shr::enums::eCharState::Skill2:
			textureName.append(L"_Skill2");
			animName = L"Skill2_Anim";
			break;
		case shr::enums::eCharState::Hit:
			textureName.append(L"_Hit");
			animName = L"Hit_Anim";
			break;
		case shr::enums::eCharState::Death:
			textureName.append(L"_Death");
			animName = L"Death_Anim";
			break;
		case shr::enums::eCharState::End:
			return;
		default:
			return;
		}

		mAnimator->Create(animName, Resources::Find<Texture>(textureName)
			, leftTop, spriteSize, offset
			, spriteLength, duration, atlasType);
	}

	void MonsterScript::PlayCharAnim(eCharState animState)
	{
		switch (animState)
		{
		case shr::enums::eCharState::None:
			break;
		case shr::enums::eCharState::Idle:
			mAnimator->Play(L"Idle_Anim");
			break;
		case shr::enums::eCharState::Run:
			mAnimator->Play(L"Run_Anim");
			break;
		case shr::enums::eCharState::Attack:
			mAnimator->Play(L"Attack_Anim");
			break;
		case shr::enums::eCharState::Attack2:
			mAnimator->Play(L"Attack2_Anim");
			break;
		case shr::enums::eCharState::Skill:
			mAnimator->Play(L"Skill_Anim");
			break;
		case shr::enums::eCharState::Skill2:
			mAnimator->Play(L"Skill2_Anim");
			break;
		case shr::enums::eCharState::Hit:
			mAnimator->Play(L"Hit_Anim");
			break;
		case shr::enums::eCharState::Death:
			mAnimator->Play(L"Death_Anim");
			break;
		default:
			break;
		}
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