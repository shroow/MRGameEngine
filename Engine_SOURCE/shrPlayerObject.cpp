#include "shrPlayerObject.h"
#include "shrSceneManager.h"
#include "shrBattleScene.h"
#include "shrStoreScene.h"
#include "shrInput.h"
#include "shrUnitObject.h"
#include "shrPlayerScript.h"
#include "shrUnitScript.h"


namespace shr
{
	PlayerObject::PlayerObject()
		: GameObject()
		, mPlayerType(ePlayerType::None)
		, mHeroType(eHeroType::None)
		, mGold(0)
		, mHP(0)
		, mLevel(0)
		, mExp(0)
		, mMaxExp(0)
		, mStoreLevel(0)
		, mDeckSize(0)
		, mUnitDeck{}
	{
		mScript = AddComponent<PlayerScript>();
		mUnitDeck.resize(0);
	}
	PlayerObject::PlayerObject(const PlayerObject& obj)
		: GameObject(obj)
		, mPlayerType(obj.mPlayerType)
		, mHeroType(obj.mHeroType)
		, mGold(obj.mGold)
		, mHP(obj.mHP)
		, mLevel(obj.mLevel)
		, mExp(obj.mExp)
		, mMaxExp(obj.mMaxExp)
		, mStoreLevel(obj.mStoreLevel)
		, mDeckSize(obj.mDeckSize)
		, mUnitDeck{}
	{
		mScript = AddComponent<PlayerScript>();
	}
	PlayerObject::~PlayerObject()
	{
	}

	void PlayerObject::Initialize()
	{
		mHP = 100;
		mGold = 3;
		mLevel = 1;
		mExp = 0;
		mMaxExp = 5;
		mStoreLevel = 3;
		mDeckSize = 3;
	}

	void PlayerObject::Update()
	{
		GameObject::Update();
		
		if (Input::GetKeyDown(eKeyCode::F))
		{
			if (SubGold(4))
				AddExp(4);
		}

		mHP;
		mGold;
		mLevel;
		mExp;
		mMaxExp;
		mStoreLevel;
		mDeckSize;

		mUnitDeck;

		int a = 0;
	}
	void PlayerObject::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void PlayerObject::Render()
	{
		//GameObject::Render();

		//HeroObject::Render();
	}

	void PlayerObject::Die()
	{
		GameObject::Die();
	}

	void PlayerObject::Battle(PlayerObject* enemy)
	{
		if (mUnitDeck.size() <= 0)
			return;

		auto iter = mUnitDeck.begin();
		auto iterEnd = mUnitDeck.end();

		while (iter != iterEnd)
		{
			if ((*iter) != nullptr)
				(*iter)->GetScript<UnitScript>()->StartBattle(enemy);

			++iter;
		}

		return;
	}

	void PlayerObject::EndBattle()
	{
		if (mUnitDeck.size() <= 0)
			return;

		auto iter = mUnitDeck.begin();
		auto iterEnd = mUnitDeck.end();

		while (iter != iterEnd)
		{
			if ((*iter) != nullptr)
				(*iter)->GetScript<UnitScript>()->EndBattle();

			++iter;
		}

		return;
	}

	bool PlayerObject::AddUnit(UnitObject* obj)
	{
		obj->SetOwner(this);
		mUnitDeck.push_back(obj);

		return true;
	}
	bool PlayerObject::DeleteUnit(UnitObject* obj)
	{
		auto iter = mUnitDeck.begin();
		auto iterEnd = mUnitDeck.end();

		while (iter != iterEnd)
		{
			if ((*iter) == obj)
			{
				(*iter)->DontDestroy(false);
				mUnitDeck.erase(iter);
				return true;
			}
			else
				++iter;
		}
		return false;
	}
	bool PlayerObject::BuyUnit(UnitObject* obj)
	{
		if ( mDeckSize <= mUnitDeck.size() )
			return false;
		
		if ( !SubGold(3) )
			return false;

		obj->GetOwner()->DeleteUnit(obj);
		obj->DontDestroy(true);
		AddUnit(obj);

		return true;
	}
	bool PlayerObject::SellUnit(UnitObject* obj)
	{
		if (DeleteUnit(obj))
		{
			AddGold(2);
			return true;
		}
		return false;
	}
	void PlayerObject::ClearDeck()
	{
		if (mUnitDeck.size() <= 0)
			return;

		auto iter = mUnitDeck.begin();
		auto iterEnd = mUnitDeck.end();

		while (iter != iterEnd)
		{
			if ((*iter) != nullptr)
			{
				(*iter)->Die();
				iter = mUnitDeck.erase(iter);
				iterEnd = mUnitDeck.end();
			}
			else
				++iter;
		}

		mUnitDeck.resize(0);
		return;
	}

	void PlayerObject::AddGold(int gold)
	{
		mGold += gold;
		if (mGold > 20)
			mGold = 20;
	}
	bool PlayerObject::SubGold(int gold)
	{
		int result = mGold - gold;

		if (result < 0)
			return false;

		mGold = result;
		return true;
	}

	void PlayerObject::AddExp(int exp)
	{
		mExp += exp;

		if (mExp == mMaxExp)
		{
			mExp = 0;
			mLevel += 1;
			if(mStoreLevel < 8)
				mStoreLevel += 1;
			mDeckSize += 1;
			mMaxExp += 5;
		}
		else if (mExp > mMaxExp)
		{
			mExp -= mMaxExp;
			mLevel += 1;
			if (mStoreLevel < 8)
				mStoreLevel += 1;
			mDeckSize += 1;
			mMaxExp += 5;
		}
	}

}