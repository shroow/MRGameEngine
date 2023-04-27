#include "shrUnitScript.h"
#include "shrGameObject.h"
#include "shrTransform.h"
#include "shrTime.h"
#include "shrInput.h"
#include "shrSpriteRenderer.h"
#include "shrFadeInScript.h"
#include "shrResources.h"
#include "shrAnimator.h"
#include "shrResource.h"
#include "shrCollisionManager.h"
#include "shrUnitStatus.h"
#include "shrUnitState.h"

namespace shr
{
	UnitScript::UnitScript()
		: Script(eScriptType::UnitScript)
		, mAnimator(nullptr)
		, mIdle(false)
		, mRun(false)
		, mDie(false)
		, mAttack(false)
		, mHit(false)
		, mbCursorOn(false)
		, mbSelected(false)
		, mbStartMove(false)
		, mMovetoPos{}
		, mSelectedPos{}
		, mPrevPos{}
		, mMove(0.f)
		, mMoveDir{}
		, mCharDir(0)
		, mState(eCharState::None)
		, mPrevState(eCharState::None)
		, mIsStore(false)
		, mIsTraded(false)
	{
	}

	UnitScript::~UnitScript()
	{
	}

	void UnitScript::Initialize()
	{
		if (mAnimator == nullptr)
			return;
		mAnimator->GetStartEvent(L"Run_Anim") = std::bind(&UnitScript::Start, this);
		mAnimator->GetCompleteEvent(L"Idle_Anim") = std::bind(&UnitScript::Action, this);
		mAnimator->GetEndEvent(L"Idle_Anim") = std::bind(&UnitScript::End, this);
		mAnimator->GetEvent(L"Idle_Anim", 1) = std::bind(&UnitScript::End, this);
	}

	void UnitScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

		Vector3 pos = tr->GetPosition();
		Status* status = mUnitStatus->GetStatus();

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

		if (mbSelected && mbCursorOn)
		{
			if (Input::GetMouseLeftDown())
			{
				mSelectedPos.x = pos.x;
				mSelectedPos.y = pos.y;

				Vector2 mousePos = Input::GetMouseWorldPos();
				pos.x = mousePos.x;
				pos.y = mousePos.y;
				mbStartMove = false;
			}

			else if (Input::GetMouseLeftPressed())
			{
				Vector2 mousePos = Input::GetMouseWorldPos();
				pos.x = mousePos.x;
				pos.y = mousePos.y;
				mbStartMove = false;
			}

			else if (Input::GetMouseLeftUp())
			{
				if (mIsTraded && mIsStore)
				{
					Vector2 mousePos = Input::GetMouseWorldPos();
					pos.x = mousePos.x;
					pos.y = mousePos.y;

					mIsStore = false;
					mIsTraded = false;
					mbStartMove = false;
				}
				else if (mIsTraded)
				{
					GetOwner()->Die();
					CollisionManager::PrevMouseCollisionSetNull();
				}
				else
				{
					pos.x = mSelectedPos.x;
					pos.y = mSelectedPos.y;

					mbStartMove = false;
				}
			}
		}
		else if (mbSelected)
		{
			if(Input::GetMouseRightDown() || Input::GetMouseRightPressed())
			{
				mMovetoPos = Input::GetMouseWorldPos();
				mbStartMove = true;
			}
		}

		//if (Input::GetKeyState(eKeyCode::R) == eKeyState::PRESSED)
		//{
		//	Vector3 rot = tr->GetRotation();
		//	rot.z += 10.0f * Time::DeltaTime();
		//	tr->SetRotation(rot);
		//}
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

		if (mbStartMove && !mIsStore)
		{
			Vector2 dir;
			float disX = mMovetoPos.x - pos.x;
			float disY = mMovetoPos.y - pos.y;
			float length = sqrt(disX * disX + disY * disY);
			dir.x = disX / length;
			dir.y = disY / length;

			pos.x += dir.x * mStatus.moveSpeed * Time::DeltaTime();
			pos.y += dir.y * mStatus.moveSpeed * Time::DeltaTime();

			mMoveDir = dir;

			disX = mMovetoPos.x - pos.x;
			disY = mMovetoPos.y - pos.y;
			if (disX < 0.002f && disX > -0.002f && disY < 0.002f && disY > -0.002f)
			{
				mbStartMove = false;
				mMoveDir = Vector2(0.f, 0.f);
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


		if (mCharDir == 1) 
			tr->SetRotation(Vector3(0.f, 180.f, 0.f));
		else
			tr->SetRotation(Vector3(0.f, 0.f, 0.f));

		tr->SetPosition(pos);
	}

	void UnitScript::FixedUpdate()
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

	void UnitScript::Render()
	{
	}

	void UnitScript::OnCollisionEnter(Collider2D* collider)
	{
		eLayerType type = collider->GetOwner()->GetLayerType();
		if(type == eLayerType::Monster)
			mAttack = true; 


		if (mbCursorOn)
		{
			if (mIsStore)
			{
				if (collider->GetName() == L"PlayerFieldCollider")
					mIsTraded = true;
			}
			else
			{
				if (collider->GetName() == L"MonsterFieldCollider")
					mIsTraded = true;
			}
		}
	}
	void UnitScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void UnitScript::OnCollisionExit(Collider2D* collider)
	{
		eLayerType type = collider->GetOwner()->GetLayerType();
		if (type == eLayerType::Monster || type == eLayerType::Player)
			mAttack = false;

		if (mIsTraded)
		{
			if (mIsStore)
			{
				if (collider->GetName() == L"PlayerFieldCollider")
					mIsTraded = false;
			}
			else
			{
				if (collider->GetName() == L"MonsterFieldCollider")
					mIsTraded = false;
			}
		}
	}
	void UnitScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void UnitScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void UnitScript::OnTriggerExit(Collider2D* collider)
	{
	}
	void UnitScript::OnMouseCollisionEnter()
	{
		mbCursorOn = true;
	}
	void UnitScript::OnMouseCollisionStay()
	{
	}
	void UnitScript::OnMouseCollisionExit()
	{
		mbCursorOn = false;
	}

	bool UnitScript::CharStateChanged()
	{
		if (mDie)
		{
			mState = eCharState::Death;
		}
		else if (mAttack)
		{
			mState = eCharState::Attack;
		}
		else if (mRun)
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
		{
			if (mMoveDir.x < 0.f)
			{
				if (mCharDir == 1)
					return false;

				mCharDir = 1;
				return true;
			}
			else if (mMoveDir.x > 0.f)
			{
				if (mCharDir == 0)
					return false;

				mCharDir = 0;
				return true;
			}
			else if (mMoveDir.x == 0.f)
				return false;
		}

		return true;
	}

	void UnitScript::SetChar(const std::wstring& name, Status status)
	{
		if (GetOwner() == nullptr)
			return;

		mAnimator = GetOwner()->AddComponent<Animator>();

		mCharName = name;

		mUnitStatus->SetStatus(status);

		mIdle = true;
	}

	void UnitScript::LoadCharAnim(eCharState animState, Vector2 offset
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

	void UnitScript::PlayCharAnim(eCharState animState, bool loop)
	{
		switch (animState)
		{
		case shr::enums::eCharState::None:
			break;
		case shr::enums::eCharState::Idle:
			mAnimator->Play(L"Idle_Anim", loop);
			break;
		case shr::enums::eCharState::Run:
			mAnimator->Play(L"Run_Anim", loop);
			break;
		case shr::enums::eCharState::Attack:
			mAnimator->Play(L"Attack_Anim", loop);
			break;
		case shr::enums::eCharState::Attack2:
			mAnimator->Play(L"Attack2_Anim", loop);
			break;
		case shr::enums::eCharState::Skill:
			mAnimator->Play(L"Skill_Anim", loop);
			break;
		case shr::enums::eCharState::Skill2:
			mAnimator->Play(L"Skill2_Anim", loop);
			break;
		case shr::enums::eCharState::Hit:
			mAnimator->Play(L"Hit_Anim", loop);
			break;
		case shr::enums::eCharState::Death:
			mAnimator->Play(L"Death_Anim", loop);
			break;
		default:
			break;
		}
	}

	void UnitScript::Battle()
	{
	}

	void UnitScript::Start()
	{
	}
	void UnitScript::Action()
	{
	}
	void UnitScript::End()
	{
	}
}