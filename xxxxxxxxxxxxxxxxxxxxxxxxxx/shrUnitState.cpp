#include "shrUnitState.h"

namespace shr
{
    UnitState::UnitState()
        : mCurrentState(eUnitState::Idle)
        , mPrevState(eUnitState::Idle)
        , mState{}
    {
        mState.reset();
    }
    UnitState::~UnitState()
    {
    }

    void UnitState::Update()
    {
        if (mState.test((UINT)eUnitState::Death))
        {
            mCurrentState = eUnitState::Death;
        }
        else if (mState.test((UINT)eUnitState::Skill2))
        {
            mCurrentState = eUnitState::Skill2;
        }
        else if (mState.test((UINT)eUnitState::Skill))
        {
            mCurrentState = eUnitState::Skill;
        }
        else if (mState.test((UINT)eUnitState::Attack2))
        {
            mCurrentState = eUnitState::Attack2;
        }
        else if (mState.test((UINT)eUnitState::Attack))
        {
            mCurrentState = eUnitState::Attack;
        }
        else if (mState.test((UINT)eUnitState::Run))
        {
            mCurrentState = eUnitState::Run;
        }
        else if (mState.test((UINT)eUnitState::Hit))
        {
            mCurrentState = eUnitState::Hit;
        }
        else if (mState.test((UINT)eUnitState::Idle))
        {
            mCurrentState = eUnitState::Idle;
        }
    }
    void UnitState::FixedUpdate()
    {
        mPrevState = mCurrentState;
    }
}