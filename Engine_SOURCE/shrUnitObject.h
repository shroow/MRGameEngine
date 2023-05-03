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

		void SetChar(eUnitType type, const std::wstring& name);
		void SetChar(eUnitType type, const std::wstring& name, Vector3 pos);
		void SetUnit(eUnitType type) { mUnitStatus.SetUnitType(type); }

		UnitStatus* GetUnitStatus() { return &mUnitStatus; }
		UnitState* GetUnitState() { return &mUnitState; }

		std::wstring GetCharName(std::wstring name) { return mUnitStatus.GetCharName(); }
		eUnitType GetUnitType(eUnitType type) { return mUnitStatus.GetUnitType(); }

		void SetAttackRange(float radius);

	public:
		UnitStatus mUnitStatus;
		UnitState mUnitState;

	private:
		GameObject* mCharUI;

		class UnitScript* mMonScript;
		class CharUIScirpt* mUIScript;
    };
}

