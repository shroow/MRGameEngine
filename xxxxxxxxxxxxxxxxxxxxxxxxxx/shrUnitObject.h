#pragma once
#include "shrGameObject.h"
#include "shrUnitStatus.h"
#include "shrUnitState.h"

namespace shr
{
    class UnitObject :
        public GameObject
    {
	public:
		UnitObject();
		UnitObject(const UnitObject& obj);
		virtual ~UnitObject();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void Die() override;

		void SetCharType(eUnitType type);
		void SetCharType(eUnitType type, Vector3 pos);

		//void SetUnit(eUnitType type) { mUnitStatus.SetUnitType(type); }
		void SetTrade(bool tf) { mTrade = tf; }
		void SetOwner(class PlayerObject* owner) { mOwner = owner; }

		UnitStatus* GetUnitStatus() { return &mUnitStatus; }
		UnitState* GetUnitState() { return &mUnitState; }

		std::wstring GetCharName(std::wstring name) { return mUnitStatus.GetCharName(); }
		eUnitType GetUnitType(eUnitType type) { return mUnitStatus.GetUnitType(); }
		bool IsTrade() { return mTrade; }
		class PlayerObject* GetOwner() { return mOwner; }

		bool SetSkill(std::wstring name);

		//??
		void SetAttackRange(float radius);
		void SetPosition(Vector3 pos);

	public:
		UnitStatus mUnitStatus;
		UnitState mUnitState;

		bool mTrade;

	private:
		class UnitUI* mCharUI;

		class UnitScript* mMonScript;
		class CharUIScirpt* mUIScript;

		class PlayerObject* mOwner;

		class Skill* mSkill;
    };
}

