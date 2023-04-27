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

		bool Action() { return mPrevState != mState; };

		void Enter(eUnitState state) { mState.set((UINT)state, true); }
		void Exit(eUnitState state) { mState.set((UINT)state, false); };

		void SetCurrentState(eUnitState state) { mCurrentState = state; }
		eUnitState GetCurrentState() { return mCurrentState; }


	private:
		eUnitState mCurrentState;
		std::bitset<(UINT)eUnitState::End> mState;
		std::bitset<(UINT)eUnitState::End> mPrevState;
	};
}

