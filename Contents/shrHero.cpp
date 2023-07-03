#include "shrHero.h"

namespace shr
{
	Hero::Hero()
		: mHeroType(eHeroType::None)
		, mStatus{}
	{
	}
	Hero::Hero(eHeroType type)
		: mHeroType(type)
		, mStatus()
	{
	}

	Hero::~Hero()
	{
	}

	void Hero::Update()
	{
	}
	void Hero::FixedUpdate()
	{
	}
}