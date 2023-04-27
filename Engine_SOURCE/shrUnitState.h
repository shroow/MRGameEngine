#pragma once
#include "shrEngine.h"

using namespace shr::enums;
namespace shr
{
	class UnitState
	{
	public:
		UnitState();
		~UnitState();

		void Update();
		void FixedUpdate();

		void Enter(eUnitState state);
		void Action(eUnitState state);
		void Exit(eUnitState state);

		void SetCurrentState(eUnitState state) { mCurrentState = state; }
		eUnitState GetCurrentState() { return mCurrentState; }


	private:
		eUnitState mCurrentState;
		std::bitset<(UINT)eUnitState::End> mState;
		std::bitset<(UINT)eUnitState::End> mPrevState;
	};
}

