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
			, attackDmg{ 10.f }, attackSpeed{ 1.f }, attackRange{ 6.5f }
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
		UnitStatus(eUnitType type);
		UnitStatus(eUnitType type, Status status);
		~UnitStatus();

		void Update();
		void FixedUpdate();

		Status* CreateStatus(Status status = Status()) { mStatus = status; return &mStatus; }

		void SetStatus(Status status) { mStatus = status; }
		void SetPosition(Vector3 position) { mPosition = position; }
		void SetUnitType(eUnitType type) { mUnitType = type; }
		void SetCharName(std::wstring name) { mCharName = name; }

		Status* GetStatus() { return &mStatus; }
		Vector3 GetPosition() { return mPosition; }
		eUnitType GetUnitType() { return mUnitType; }
		const std::wstring& GetCharName() { return mCharName; }

		void AddBuff(eBuffType buff, float value) { buffVec[(UINT)buff].push_back(value); }
		std::vector<float>& GetBuffVec() { return *buffVec; }
		void ClearBuff() { buffVec->clear(); }

	private:
		eUnitType mUnitType;
		std::wstring mCharName;
		Status mStatus;
		Vector3 mPosition;

		std::vector<float> buffVec[(UINT)eBuffType::End];
	};
}

