#include "shrPlayerObject.h"

namespace shr
{
	PlayerObject::PlayerObject()
	{
	}
	PlayerObject::PlayerObject(const PlayerObject& obj)
	{
	}
	PlayerObject::~PlayerObject()
	{
	}
	void PlayerObject::Initialize()
	{
	}
	void PlayerObject::Update()
	{
	}
	void PlayerObject::FixedUpdate()
	{
	}
	void PlayerObject::Render()
	{
	}
	void PlayerObject::BuyUnit()
	{
	}
	void PlayerObject::SellUnit()
	{
	}
	void PlayerObject::AddGold(int gold)
	{
		mGold += gold;
		if (mGold > 10)
			mGold = 10;
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