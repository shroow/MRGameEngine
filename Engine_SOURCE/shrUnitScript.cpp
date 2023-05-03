#include "shrUnitScript.h"
#include "shrTime.h"
#include "shrInput.h"
#include "shrSpriteRenderer.h"
#include "shrFadeInScript.h"
#include "shrResources.h"
#include "shrUnitObject.h"
#include "shrAnimator.h"
#include "shrResource.h"
#include "shrCollisionManager.h"

namespace shr
{
	UnitScript::UnitScript()
		: Script(eScriptType::UnitScript)
		, mAnimator(nullptr)
		, mTransform(nullptr)
		, mUnitStatus(nullptr)
		, mUnitState(nullptr)
		, mbCursorOn(false)
		, mbSelected(false)
		, mbStartMove(false)
		, mMovetoPos{}
		, mSelectedPos{}
		, mPrevPos{}
		, mMove(0.f)
		, mMoveDir{}
		, mIsDirLeft(false)
		, mIsStore(false)
		, mIsTraded(false)
	{
	}

	UnitScript::~UnitScript()
	{
	}

	void UnitScript::Initialize()
	{
		mOwner = (UnitObject*)GetOwner();

		mTransform = mOwner->GetComponent<Transform>();

		mUnitStatus = mOwner->GetUnitStatus();
		mUnitState = mOwner->GetUnitState();

		if (mAnimator == nullptr)
			return;

		mAnimator->GetStartEvent(L"Run_Anim") = std::bind(&UnitScript::Start, this);
		mAnimator->GetCompleteEvent(L"Idle_Anim") = std::bind(&UnitScript::Action, this);
		mAnimator->GetEndEvent(L"Idle_Anim") = std::bind(&UnitScript::End, this);
		mAnimator->GetEvent(L"Idle_Anim", 1) = std::bind(&UnitScript::End, this);
	}

	void UnitScript::Update()
	{
		MouseControl();
		Move();

		if (mIsBattle)
			Battle();

		mUnitState->Update();
		mUnitStatus->Update();
	}

	void UnitScript::FixedUpdate()
	{
		if (mAnimator == nullptr)
			return;

		CheckUnitState();

		if (!UnitStateChanged()) //¾È ¹Ù²î¾úÀ¸¸é ¸ØÃã
			return;

		if (Input::GetKeyDown(eKeyCode::N_0))
			StartBattle();

		PlayUnitAnim(mUnitState->GetCurrentState());

		mUnitState->FixedUpdate();
		mUnitStatus->FixedUpdate();
	}

	void UnitScript::Render()
	{
	}

	void UnitScript::MouseControl()
	{
		Vector3 pos = mTransform->GetPosition();

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
		else if (mbSelected && !mIsStore)
		{
			if (Input::GetMouseRightDown() || Input::GetMouseRightPressed())
			{
				mMovetoPos = Input::GetMouseWorldPos();
				mbStartMove = true;
			}
		}

		mTransform->SetPosition(pos);
	}

	void UnitScript::Move()
	{
		Vector3 pos = mTransform->GetPosition();
		Status* status = mUnitStatus->GetStatus();

		if (mbStartMove)
		{
			Vector2 dir;
			float disX = mMovetoPos.x - pos.x;
			float disY = mMovetoPos.y - pos.y;
			float length = sqrt(disX * disX + disY * disY);
			dir.x = disX / length;
			dir.y = disY / length;

			pos.x += dir.x * status->moveSpeed * Time::DeltaTime();
			pos.y += dir.y * status->moveSpeed * Time::DeltaTime();

			mMoveDir = dir;

			if (disX > 0.f)
				mIsDirLeft = false;
			else if (disX < 0.f)
				mIsDirLeft = true;


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

			mUnitState->Enter(eUnitState::Run);
			mUnitState->Exit(eUnitState::Idle);
		}
		else
		{
			mMove = 0.f;

			mUnitState->Enter(eUnitState::Idle);
			mUnitState->Exit(eUnitState::Run);
		}


		if (mIsDirLeft)
			mTransform->SetRotation(Vector3(0.f, 180.f, 0.f));
		else
			mTransform->SetRotation(Vector3(0.f, 0.f, 0.f));

		mPrevPos = pos;
		mTransform->SetPosition(pos);
	}

	void UnitScript::Battle()
	{
	}

	void UnitScript::CheckUnitState()
	{
		Status* status = mUnitStatus->GetStatus();

		if (status->HP == 0.f)
			mUnitState->Enter(eUnitState::Death);
	}

	bool UnitScript::UnitStateChanged()
	{
		if (!mUnitState->Action())
			return false;

		return true;
	}

	void UnitScript::OnCollisionEnter(Collider2D* collider)
	{
		eComponentType compType = collider->GetOrder();
		if (compType == eComponentType::Collider)
		{
			eLayerType type = collider->GetOwner()->GetLayerType();
			if (type == eLayerType::Monster || type == eLayerType::Player)
				mUnitState->Enter(eUnitState::Attack);

			else if (type == eLayerType::Background)
			{
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
		}
		else if (compType == eComponentType::Collider2)
		{

		}
	}
	void UnitScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void UnitScript::OnCollisionExit(Collider2D* collider)
	{
		eComponentType compType = collider->GetOrder();
		if (compType == eComponentType::Collider2)
			int a = 0; // do action

		eLayerType type = collider->GetOwner()->GetLayerType();
		if (type == eLayerType::Monster || type == eLayerType::Player)
			mUnitState->Exit(eUnitState::Attack);

		else if (type == eLayerType::Background)
		{
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

	void UnitScript::SetChar(const std::wstring& name)
	{
		if (mOwner == nullptr)
			return;

		mAnimator = mOwner->GetComponent<Animator>();

		mCharName = name;
	}

	void UnitScript::LoadUnitAnim(const std::wstring& name)
	{
	}

	void UnitScript::LoadUnitAnim(eUnitState animState, Vector2 offset
		, Vector2 leftTop, Vector2 spriteSize
		, UINT spriteLength, float duration, eAtlasType atlasType)
	{
		std::wstring textureName;
		std::wstring animName;

		textureName = mCharName;

		switch (animState)
		{
		case shr::enums::eUnitState::Idle:
			textureName.append(L"_Idle");
			animName = L"Idle_Anim";
			break;
		case shr::enums::eUnitState::Run:
			textureName.append(L"_Run");
			animName = L"Run_Anim";
			break;
		case shr::enums::eUnitState::Attack:
			textureName.append(L"_Attack");
			animName = L"Attack_Anim";
			break;
		case shr::enums::eUnitState::Attack2:
			textureName.append(L"_Attack2");
			animName = L"Attack2_Anim";
			break;
		case shr::enums::eUnitState::Skill:
			textureName.append(L"_Skill");
			animName = L"Skill_Anim";
			break;
		case shr::enums::eUnitState::Skill2:
			textureName.append(L"_Skill2");
			animName = L"Skill2_Anim";
			break;
		case shr::enums::eUnitState::Hit:
			textureName.append(L"_Hit");
			animName = L"Hit_Anim";
			break;
		case shr::enums::eUnitState::Death:
			textureName.append(L"_Death");
			animName = L"Death_Anim";
			break;
		case shr::enums::eUnitState::End:
			return;
		}

		mAnimator->Create(animName, Resources::Find<Texture>(textureName)
			, leftTop, spriteSize, offset
			, spriteLength, duration, atlasType);
	}

	void UnitScript::PlayUnitAnim(eUnitState animState, bool loop)
	{
		switch (animState)
		{
		case shr::enums::eUnitState::Idle:
			mAnimator->Play(L"Idle_Anim", loop);
			break;
		case shr::enums::eUnitState::Run:
			mAnimator->Play(L"Run_Anim", loop);
			break;
		case shr::enums::eUnitState::Attack:
			mAnimator->Play(L"Attack_Anim", loop);
			break;
		case shr::enums::eUnitState::Attack2:
			mAnimator->Play(L"Attack2_Anim", loop);
			break;
		case shr::enums::eUnitState::Skill:
			mAnimator->Play(L"Skill_Anim", loop);
			break;
		case shr::enums::eUnitState::Skill2:
			mAnimator->Play(L"Skill2_Anim", loop);
			break;
		case shr::enums::eUnitState::Hit:
			mAnimator->Play(L"Hit_Anim", loop);
			break;
		case shr::enums::eUnitState::Death:
			mAnimator->Play(L"Death_Anim", loop);
			break;
		default:
			break;
		}
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