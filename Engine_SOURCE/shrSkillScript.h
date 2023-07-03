#pragma once
#include "shrScript.h"

namespace shr
{
    class SkillScript :
        public Script
    {
    public:
        SkillScript();
        ~SkillScript();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

        void Move();

        virtual void OnCollisionEnter(Collider2D* collider) override;
        virtual void OnCollisionStay(Collider2D* collider) override;
        virtual void OnCollisionExit(Collider2D* collider) override;

        virtual void OnTriggerEnter(Collider2D* collider) override;
        virtual void OnTriggerStay(Collider2D* collider) override;
        virtual void OnTriggerExit(Collider2D* collider) override;

        virtual void OnMouseCollisionEnter() override;
        virtual void OnMouseCollisionStay() override;
        virtual void OnMouseCollisionExit() override;


        void SetSkillAnim(eUnitType type);
        void LoadSkillAnim(eUnitType type);
        void LoadSkillAnim(eUnitState animState, Vector2 offset
            , Vector2 leftTop, Vector2 spriteSize
            , UINT spriteLength, float duration, eAtlasType atlasType = eAtlasType::Column);

        void Start();
        void Action();
        void End();

        void AttackComplete();
        void SkillActive();


    private:
        //Class Ctrl
        class PlayerObject* mEnemy;
        class UnitObject* mOwner;
        class Animator* mAnimator;
        class Transform* mTransform;

        //Move Ctrl
        bool mbStartMove;
        Vector2 mMovetoPos;
        Vector2 mSelectedPos;
        Vector3 mPrevPos;
        float mMove;
        Vector2 mMoveDir;
        bool mIsDirLeft;

        eSkillType mSkillType;
    };
}

