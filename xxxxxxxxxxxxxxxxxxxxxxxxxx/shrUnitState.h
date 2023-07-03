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

		bool Action() { return mPrevState != mCurrentState; };

		void Enter(eUnitState state) { mState.set(state, true); }
		void Exit(eUnitState state) { mState.set(state, false); };

		void SetCurrentState(eUnitState state) { mCurrentState = state; }
		eUnitState GetCurrentState() { return mCurrentState; }

	private:
		eUnitState mCurrentState;
		eUnitState mPrevState;
		std::bitset<eUnitState::End> mState;
	};
}

