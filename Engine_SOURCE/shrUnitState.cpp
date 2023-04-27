#include "shrUnitState.h"

namespace shr
{
    UnitState::UnitState()
        : mCurrentState(eUnitState::Idle)
        , mState{}
        , mPrevState{}
    {
        mPrevState.reset();
        mState.reset();
        mState.set((UINT)mCurrentState, true);
    }
    UnitState::~UnitState()
    {
    }

    void UnitState::Update()
    {
    }

    void UnitState::FixedUpdate()
    {
    }

    void UnitState::Enter(eUnitState state)
    {
        mState.set((UINT)state, true);
    }
    void UnitState::Action(eUnitState state)
    {


    }
    void UnitState::Exit(eUnitState state)
    {
        mState.set((UINT)state, false);
    }
}