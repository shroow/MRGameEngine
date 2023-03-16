#pragma once
#include "shrScript.h"
#include "shrResources.h"

namespace shr
{
    class MonsterScript :
        public Script
    {
    public:
        enum eState
        {
            Idle,
            Attack,
            Die,
            End
        };

        struct Status
        {
            float HP;
            float maxHP;
            float MP;
            float maxMP;

            float attackDmg;
            float attackSpeed;

            float moveSpeed;
            eMoveType moveType;

            //Skill needed

            std::vector<float> buffVec[(UINT)eBuffType::End];
        };


        MonsterScript();
        ~MonsterScript();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

        void LoadResources();

        virtual void OnCollisionEnter(Collider2D* collider) override;
        virtual void OnCollisionStay(Collider2D* collider) override;
        virtual void OnCollisionExit(Collider2D* collider) override;

        virtual void OnTriggerEnter(Collider2D* collider) override;
        virtual void OnTriggerStay(Collider2D* collider) override;
        virtual void OnTriggerExit(Collider2D* collider) override;

    private:
        Transform* mOwnerTR;
        class Animator* mAnimator;

        bool mIdle;
        bool mMove;
        bool mDie;
        bool mAttack;
        bool mChange;

        Status mStatus;
    };
}

