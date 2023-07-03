#include "shrUnitScript.h"
#include "shrTime.h"
#include "shrInput.h"
#include "shrSpriteRenderer.h"
#include "shrFadeInScript.h"
#include "shrResources.h"
#include "shrPlayerObject.h"
#include "shrUnitObject.h"
#include "shrAnimator.h"
#include "shrResources.h"
#include "shrCollisionManager.h"
#include "shrUnitInfo.h"
#include "shrSceneManager.h"
#include <float.h>// FLT_MAX


namespace shr
{
	UnitScript::UnitScript()
		: Script(eScriptType::UnitScript)
		, mAnimator(nullptr)
		, mTransform(nullptr)
		, mUnitStatus(nullptr)
		, mUnitState(nullptr)
		, mEnemy(nullptr)
		, mOwner(nullptr)
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
		, mIsBattle(false)
		, mStartPos{}
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
	}

	void UnitScript::Update()
	{
		if (mIsBattle)
			Battle();
		else
			MouseControl();

		Move();

		mUnitState->Update();
		mUnitStatus->Update();
	}

	void UnitScript::FixedUpdate()
	{
		Vector3 pos = mOwner->GetComponent<Transform>()->GetPosition();
		mPrevPos = pos;

		if (mAnimator == nullptr)
			return;

		CheckUnitState();

		if (!UnitStateChanged()) //¾È ¹Ù²î¾úÀ¸¸é ¸ØÃã
			return;

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

		if (mbCursorOn && Input::GetMouseLeftDown())
			mbSelected = true;


		if (mbSelected)
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
				if (mOwner->IsTrade() && mIsStore)
				{
					PlayerObject* player = SceneManager::GetPlayer();

					if (player->BuyUnit(mOwner))
					{
						Vector2 mousePos = Input::GetMouseWorldPos();
						pos.x = mousePos.x;
						pos.y = mousePos.y;

						mIsStore = false;
						mOwner->SetTrade(false);
						mbStartMove = false;
						mbSelected = false;
					}
					else
					{
						pos.x = mSelectedPos.x;
						pos.y = mSelectedPos.y;

						mbStartMove = false;
						mbSelected = false;
					}
				}
				else if (mOwner->IsTrade())
				{

					PlayerObject* player = SceneManager::GetPlayer();

					if(player->SellUnit(mOwner))
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
				else
				{
					pos.x = mSelectedPos.x;
					pos.y = mSelectedPos.y;

					mbStartMove = false;
					mbSelected = false;
				}
			}
		}


		if (mbSelected && !mIsStore)
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

		//mPrevPos = pos;
		mTransform->SetPosition(pos);
	}

	void UnitScript::Battle()
	{
		std::vector<UnitObject*>& enemyUnits = mEnemy->GetUnitDeck();

		UnitObject* unit;
		UnitObject* closestEnemyUnit = nullptr;

		float closestDistance = FLT_MAX;

		for (UnitObject* enemyUnit : enemyUnits)
		{
			Transform* tr = mTransform;
			Transform* emTr = enemyUnit->GetComponent<Transform>();
			Vector2 pos = Vector2(tr->GetPosition().x, tr->GetPosition().y);
			Vector2 emPos = Vector2(emTr->GetPosition().x, emTr->GetPosition().y);

			float distance = Vector2::Distance(pos, emPos);

			if (distance < closestDistance) {
				closestDistance = distance;
				closestEnemyUnit = enemyUnit;
			}
		}

		if (closestEnemyUnit != nullptr)
		{
			float attackRange = mUnitStatus->GetStatus()->attackRange;

			if (attackRange >= closestDistance)
			{
				Attack();
			}
			else
				Attack(closestEnemyUnit);
		}
	}

	void UnitScript::Battle(PlayerObject* enemy)
	{
		std::vector<UnitObject*>& enemyUnits = enemy->GetUnitDeck();

		UnitObject* unit; 
		UnitObject* closestEnemyUnit = nullptr;

		float closestDistance = FLT_MAX;

		for (UnitObject* enemyUnit : enemyUnits) 
		{
			Transform* tr = mTransform;
			Transform* emTr = enemyUnit->GetComponent<Transform>();
			Vector2 pos = Vector2(tr->GetPosition().x, tr->GetPosition().y);
			Vector2 emPos = Vector2(emTr->GetPosition().x, emTr->GetPosition().y);

			float distance = Vector2::Distance(pos, emPos);

			if (distance < closestDistance) {
				closestDistance = distance;
				closestEnemyUnit = enemyUnit;
			}
		}

		if (closestEnemyUnit != nullptr)
		{
			float attackRange = mUnitStatus->GetStatus()->attackRange;
			
			if (attackRange >= closestDistance)
			{
				Attack();
			}
			else
				Attack(closestEnemyUnit);
		}
	}

	void UnitScript::StartBattle(PlayerObject* enemy)
	{
		mEnemy = enemy; 
		mIsBattle = true;

		mStartPos = mTransform->GetPosition();
	}

	void UnitScript::EndBattle()
	{
		mEnemy = nullptr; 
		mIsBattle = false;

		mUnitState->Exit(eUnitState::Attack);
		mbStartMove = false;

		mTransform->SetPosition(mStartPos);
	}

	void UnitScript::Attack()
	{
		if (mUnitStatus->IsMaxMP())
		{
			mUnitState->Enter(eUnitState::Skill);
		}
		mUnitState->Enter(eUnitState::Attack);
		mbStartMove = false;
	}

	void UnitScript::Attack(UnitObject* target)
	{
		Vector3 emPos = target->GetComponent<Transform>()->GetPosition();

		mMovetoPos = Vector2(emPos.x, emPos.y);
		mbStartMove = true;
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
			{
				//mUnitState->Enter(eUnitState::Attack);
			}
			else if (type == eLayerType::Background)
			{
				if (mbCursorOn)
				{
					if (mIsStore)
					{
						if (collider->GetName() == L"PlayerFieldCollider")
							mOwner->SetTrade(true);
					}
					else
					{
						if (collider->GetName() == L"MonsterFieldCollider")
							mOwner->SetTrade(true);
					}
				}
			}
		}
		else if (compType == eComponentType::Collider2)
		{
			if (mIsBattle)
			{
				eLayerType type = collider->GetOwner()->GetLayerType();

				if (type == eLayerType::Monster2)
				{
					mUnitState->Enter(eUnitState::Attack);
				}
			}
		}
	}
	void UnitScript::OnCollisionStay(Collider2D* collider)
	{
		eLayerType type = collider->GetOwner()->GetLayerType();

		if (type == eLayerType::Monster2)
		{
			int a = 0;
		}
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
			if (mOwner->IsTrade())
			{
				if (mIsStore)
				{
					if (collider->GetName() == L"PlayerFieldCollider")
						mOwner->SetTrade(false);
				}
				else
				{
					if (collider->GetName() == L"MonsterFieldCollider")
						mOwner->SetTrade(false);
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

	void UnitScript::SetUnitAnim(eUnitType type)
	{
		if (mOwner == nullptr)
			return;

		mAnimator = mOwner->GetComponent<Animator>();
	}

	void UnitScript::LoadUnitAnim(eUnitType type)
	{
		std::wstring animName;

		UINT unitType = (UINT)mUnitStatus->GetUnitType();
		std::wstringstream ss; 
		ss << unitType;

		for (UINT i = 0; i < (UINT)eUnitState::End; ++i)
		{
			if( i == (UINT)eUnitState::Idle)
			{
				std::wstring textureName = ss.str();
				textureName.append(L"_Idle");
				animName = L"Idle_Anim";

				UnitInfo* info;
				info = GetUnitInfo(type, (eUnitState)i);

				mAnimator->Create(animName, Resources::Find<Texture>(textureName)
					, info->leftTop, info->spriteSize, info->offset
					, info->spriteLength, info->duration, info->atlasType);

				delete info;
			}
			else if( i == (UINT)eUnitState::Run)
			{
				std::wstring textureName = ss.str();
				textureName.append(L"_Run");
				animName = L"Run_Anim";

				UnitInfo* info;
				info = GetUnitInfo(type, (eUnitState)i);

				mAnimator->Create(animName, Resources::Find<Texture>(textureName)
					, info->leftTop, info->spriteSize, info->offset
					, info->spriteLength, info->duration, info->atlasType);

				delete info;
			}
			else if( i == (UINT)eUnitState::Attack)
			{
				std::wstring textureName = ss.str();
				textureName.append(L"_Attack");
				animName = L"Attack_Anim";

				UnitInfo* info;
				info = GetUnitInfo(type, (eUnitState)i);

				mAnimator->Create(animName, Resources::Find<Texture>(textureName)
					, info->leftTop, info->spriteSize, info->offset
					, info->spriteLength, info->duration, info->atlasType);

				delete info;
			}
			else if( i == (UINT)eUnitState::Skill)
			{
				std::wstring textureName = ss.str();
				textureName.append(L"_Skill");
				animName = L"Skill_Anim";

				UnitInfo* info;
				info = GetUnitInfo(type, (eUnitState)i);

				mAnimator->Create(animName, Resources::Find<Texture>(textureName)
					, info->leftTop, info->spriteSize, info->offset
					, info->spriteLength, info->duration, info->atlasType);

				delete info;
			}
			else if( i == (UINT)eUnitState::Hit)
			{
				std::wstring textureName = ss.str();
				textureName.append(L"_Hit");
				animName = L"Hit_Anim";

				UnitInfo* info;
				info = GetUnitInfo(type, (eUnitState)i);

				mAnimator->Create(animName, Resources::Find<Texture>(textureName)
					, info->leftTop, info->spriteSize, info->offset
					, info->spriteLength, info->duration, info->atlasType);

				delete info;
			}
			else if( i == (UINT)eUnitState::Death)
			{
				std::wstring textureName = ss.str();
				textureName.append(L"_Death");
				animName = L"Death_Anim";

				UnitInfo* info;
				info = GetUnitInfo(type, (eUnitState)i);

				mAnimator->Create(animName, Resources::Find<Texture>(textureName)
					, info->leftTop, info->spriteSize, info->offset
					, info->spriteLength, info->duration, info->atlasType);

				delete info;
			}
		}

		//mAnimator->GetStartEvent(L"Run_Anim") = std::bind(&UnitScript::Start, this);
		//mAnimator->GetCompleteEvent(L"Idle_Anim") = std::bind(&UnitScript::Action, this);
		//mAnimator->GetEndEvent(L"Idle_Anim") = std::bind(&UnitScript::End, this);
		//mAnimator->GetEvent(L"Idle_Anim", 1) = std::bind(&UnitScript::End, this);

		mAnimator->GetCompleteEvent(L"Attack_Anim") = std::bind(&UnitScript::AttackComplete, this);
		mAnimator->GetStartEvent(L"Skill_Anim") = std::bind(&UnitScript::SkillActive, this);
	}

	void UnitScript::LoadUnitAnim(eUnitState animState, Vector2 offset
		, Vector2 leftTop, Vector2 spriteSize
		, UINT spriteLength, float duration, eAtlasType atlasType)
	{
		std::wstring animName;

		UINT unitType = (UINT)mUnitStatus->GetUnitType();
		std::wstringstream ss; ss << unitType;

		std::wstring textureName = ss.str();

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
		//case shr::enums::eUnitState::Attack2:
		//	textureName.append(L"_Attack2");
		//	animName = L"Attack2_Anim";
		//	break;
		case shr::enums::eUnitState::Skill:
			textureName.append(L"_Skill");
			animName = L"Skill_Anim";
			break;
		//case shr::enums::eUnitState::Skill2:
		//	textureName.append(L"_Skill2");
		//	animName = L"Skill2_Anim";
		//	break;
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
	void UnitScript::AttackComplete()
	{
		mUnitStatus->AddMP(10.f);
	}
	void UnitScript::SkillActive()
	{
		mUnitStatus->GetStatus()->MP = 0.f;
	}
}