#pragma once
#include "shrEnums.h"
#include "shrMath.h"

using namespace shr::enums;
using namespace shr::math;

namespace shr
{
	struct Status
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

		Status() : maxHP{ 100.f }, HP{ 100.f }, maxMP{ 100.f }, MP{ 20.f }
			, attackDmg{ 10.f }, attackSpeed{ 1.f }, attackRange{ 10.f }
			, moveSpeed{ 10.f }, moveType{ eMoveType::Ground } {}

		Status(float hp, float MaxHP, float mp, float MaxMP, float AttackDmg, float AttackSpeed
			, float AttackRange, float MoveSpeed, eMoveType MoveType)
			: maxHP{ MaxHP }, HP{ hp }, maxMP{ MaxMP }, MP{ mp }
			, attackDmg{ AttackDmg }, attackSpeed{ AttackSpeed }, attackRange{ AttackRange }
			, moveSpeed{ MoveSpeed }, moveType{ MoveType } {}


		Status(const Status&) = default;
		Status& operator=(const Status&) = default;
	};

	class UnitStatus
	{
	public:
		UnitStatus();
		~UnitStatus();

		void Update();
		void FixedUpdate();

		Status* CreateStatus(Status status = Status()) { mStatus = status; return &mStatus; }

		void SetStatus(Status status) { mStatus = status; }
		Status* GetStatus() { return &mStatus; }

		void AddBuff(eBuffType buff, float value) { buffVec[(UINT)buff].push_back(value); }
		std::vector<float>& GetBuffVec() { return *buffVec; }
		void ClearBuff() { buffVec->clear(); }

	private:
		Status mStatus;
		std::vector<float> buffVec[(UINT)eBuffType::End];
	};
}

