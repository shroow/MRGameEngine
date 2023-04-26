#pragma once
#include "shrScript.h"
#include "shrResources.h"
#include "shrAnimator.h"

namespace shr
{
    class MonsterScript :
        public Script
    {
    public:
        MonsterScript();
        ~MonsterScript();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

        virtual void OnCollisionEnter(Collider2D* collider) override;
        virtual void OnCollisionStay(Collider2D* collider) override;
        virtual void OnCollisionExit(Collider2D* collider) override;

        virtual void OnTriggerEnter(Collider2D* collider) override;
        virtual void OnTriggerStay(Collider2D* collider) override;
        virtual void OnTriggerExit(Collider2D* collider) override;

        virtual void OnMouseCollisionEnter() override;
        virtual void OnMouseCollisionStay() override;
        virtual void OnMouseCollisionExit() override;

        bool CharStateChanged();
        void SetChar(const std::wstring& name, Status status = {});
        void LoadCharAnim(eCharState animState, Vector2 offset
            , Vector2 leftTop, Vector2 spriteSize
            , UINT spriteLength, float duration, eAtlasType atlasType = eAtlasType::Column);
        void PlayCharAnim(eCharState animState, bool loop = true);

        void Battle();

        void Start();
        void Action();
        void End();

        void SetCharName(const std::wstring& name) { mCharName = name; }
        eCharState GetCharState() { return mState; }
        void SetCharState(eCharState state) { mState = state; mPrevState = eCharState::None; }

        bool GetIsStore() { return mIsStore; }
        void SetIsStore(bool tf) { mIsStore = tf; }

    private:
        std::wstring mCharName;
        Animator* mAnimator;

        Status mStatus;
        bool mIdle;
        bool mRun;
        bool mDie;
        bool mAttack;
        bool mHit;

        bool mbCursorOn;
        bool mbSelected;
        bool mbStartMove;
        Vector2 mMovetoPos;
        Vector2 mSelectedPos;

        Vector3 mPrevPos;
        float mMove;
        Vector2 mMoveDir;
        int mCharDir;

        eCharState mState;
        eCharState mPrevState;

        bool mIsStore;
        bool mIsTraded;
    };
}

