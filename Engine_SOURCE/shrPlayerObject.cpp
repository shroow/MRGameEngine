#include "shrPlayerObject.h"
#include "shrSceneManager.h"
#include "shrBattleScene.h"
#include "shrStoreScene.h"

namespace shr
{
	PlayerObject::PlayerObject()
		: GameObject()
		, mGold(0)
		, mHP(0)
		, mDeckSize(0)
		, mHeroType(eHeroType::None)
		, mUnitDeck{}
		, mScript(nullptr)
	{
		mScript = AddComponent<PlayerScript>();
	}
	PlayerObject::PlayerObject(const PlayerObject& obj)
		: GameObject(obj)
		, mGold(obj.mGold)
		, mHP(obj.mHP)
		, mDeckSize(obj.mDeckSize)
		, mHeroType(obj.mHeroType)
		, mUnitDeck{}
		, mScript(nullptr)
	{
		mUnitDeck = obj.mUnitDeck;

		mScript = AddComponent<PlayerScript>();
	}
	PlayerObject::~PlayerObject()
	{
	}

	void PlayerObject::Initialize()
	{
		GameObject::Initialize();

		mGold = 3;
		mDeckSize = 3;
	}
	void PlayerObject::Update()
	{
		GameObject::Update();

		Scene* scene = SceneManager::GetActiveScene();
		
		eSceneType sceneType = scene->GetSceneType();

		if (sceneType == eSceneType::Store)
		{

		}
		else if (sceneType == eSceneType::Battle)
		{ 
			auto iter = mUnitDeck.begin();
			auto iterEnd = mUnitDeck.end();

			while (iter != iterEnd)
			{
				if ((*iter) == nullptr)
					break;


				++iter;
			}
		}

	}
	void PlayerObject::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void PlayerObject::Render()
	{
		GameObject::Render();
	}

	bool PlayerObject::BuyUnit(UnitObject* obj)
	{
		if (mDeckSize <= mUnitDeck.size())
			return false;
		
		if (!SubGold(3))
			return false;

		obj->DontDestroy(true);
		mUnitDeck.push_back(obj);

		return true;
	}
	bool PlayerObject::SellUnit(UnitObject* obj)
	{
		auto iter = mUnitDeck.begin();
		auto iterEnd = mUnitDeck.end();

		while (iter != iterEnd)
		{
			if ((*iter) == obj)
			{
				obj->DontDestroy(false);
				obj->Die();
				AddGold(2);
				return true;
			}
			++iter;
		}

		return false;
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
	void PlayerObject::Battle()
	{
	}
}