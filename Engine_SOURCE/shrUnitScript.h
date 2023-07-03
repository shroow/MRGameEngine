#pragma once
#include "shrScript.h"

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
        void Battle(class PlayerObject* enemy);
        void StartBattle(class PlayerObject* enemy);
        void EndBattle();

        void Attack();
        void Attack(class UnitObject* target);

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


        void SetUnitAnim(eUnitType type);
        void LoadUnitAnim(eUnitType type);
        void LoadUnitAnim(eUnitState animState, Vector2 offset
            , Vector2 leftTop, Vector2 spriteSize
            , UINT spriteLength, float duration, eAtlasType atlasType = eAtlasType::Column);
        void PlayUnitAnim(eUnitState animState, bool loop = true);

        void Start();
        void Action();
        void End();

        void AttackComplete();
        void SkillActive();

        void SetIsStore(bool tf) { mIsStore = tf; }
        bool GetIsStore() { return mIsStore; }
        void SetStartPos(Vector3 pos) { mStartPos = pos; }

    public:
        eUnitType mUnitType;

        class UnitStatus* mUnitStatus;
        class UnitState* mUnitState;

    private:
        //Class Ctrl
        class PlayerObject* mEnemy;
        class UnitObject* mOwner;
        class Animator* mAnimator;
        class Transform* mTransform;

        //Mouse Ctrl
        bool mbCursorOn;
        bool mbSelected;

        //Move Ctrl
        bool mbStartMove;
        Vector2 mMovetoPos;
        Vector2 mSelectedPos;
        Vector3 mPrevPos;
        float mMove;
        Vector2 mMoveDir;
        bool mIsDirLeft;


        bool mIsStore;
        bool mIsBattle;
        Vector3 mStartPos;
    };
}

