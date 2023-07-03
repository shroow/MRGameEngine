#pragma once
#include "shrEnums.h"

using namespace shr::enums;
namespace shr
{
	struct HeroStatus
	{
		float maxHP;
		float HP;
		float maxMP;
		float MP;

		float attackDmg;
		float attackSpeed;
		float attackRange;

		float moveSpeed;
		eMoveType moveType;

		HeroStatus() : maxHP{ 100.f }, HP{ 100.f }, maxMP{ 100.f }, MP{ 20.f }
			, attackDmg{ 10.f }, attackSpeed{ 1.f }, attackRange{ 10.f }
			, moveSpeed{ 10.f }, moveType{ eMoveType::Ground } {}

		HeroStatus(float hp, float MaxHP, float mp, float MaxMP, float AttackDmg, float AttackSpeed
			, float AttackRange, float MoveSpeed, eMoveType MoveType)
			: maxHP{ MaxHP }, HP{ hp }, maxMP{ MaxMP }, MP{ mp }
			, attackDmg{ AttackDmg }, attackSpeed{ AttackSpeed }, attackRange{ AttackRange }
			, moveSpeed{ MoveSpeed }, moveType{ MoveType } {}


		HeroStatus(const HeroStatus&) = default;
		HeroStatus& operator=(const HeroStatus&) = default;
	};

	class Hero
	{
	public:
		Hero();
		Hero(eHeroType type);
		~Hero();

		void Update();
		void FixedUpdate();

	private:
		eHeroType mHeroType;
		HeroStatus mStatus;
	};
}

