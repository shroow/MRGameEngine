#pragma once
#include "shrScript.h"
#include "shrResources.h"
#include "shrAnimator.h"
#include "shrUnitObject.h"

namespace shr
{
    class UnitScript :
        public Script
    {
    public:
        UnitScript();
        ~UnitScript();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

        void MouseControl();
        void Move();
        void Battle();

        void CheckUnitState();
        bool UnitStateChanged();

        virtual void OnCollisionEnter(Collider2D* collider) override;
        virtual void OnCollisionStay(Collider2D* collider) override;
        virtual void OnCollisionExit(Collider2D* collider) override;

        virtual void OnTriggerEnter(Collider2D* collider) override;
        virtual void OnTriggerStay(Collider2D* collider) override;
        virtual void OnTriggerExit(Collider2D* collider) override;

        virtual void OnMouseCollisionEnter() override;
        virtual void OnMouseCollisionStay() override;
        virtual void OnMouseCollisionExit() override;

        void SetChar(const std::wstring& name, Status status = {});
        void LoadUnitAnim(eUnitState animState, Vector2 offset
            , Vector2 leftTop, Vector2 spriteSize
            , UINT spriteLength, float duration, eAtlasType atlasType = eAtlasType::Column);
        void PlayUnitAnim(eUnitState animState, bool loop = true);

        void Start();
        void Action();
        void End();

        void SetCharName(const std::wstring& name) { mCharName = name; }

        void SetIsStore(bool tf) { mIsStore = tf; }
        bool GetIsStore() { return mIsStore; }
        void StartBattle() { mIsBattle = true; }

    public:
        std::wstring mCharName;

        UnitStatus* mUnitStatus;
        UnitState* mUnitState;

    private:
        UnitObject* mOwner;
        Animator* mAnimator;
        Transform* mTransform;

        bool mbCursorOn;
        bool mbSelected;
        bool mbStartMove;
        Vector2 mMovetoPos;
        Vector2 mSelectedPos;

        Vector3 mPrevPos;
        float mMove;
        Vector2 mMoveDir;
        bool mIsDirLeft;


        bool mIsStore;
        bool mIsTraded;
        bool mIsBattle;
    };
}

