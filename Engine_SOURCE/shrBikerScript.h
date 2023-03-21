#pragma once
#include "shrScript.h"
#include "shrResources.h"

namespace shr
{
    class BikerScript :
        public Script
    {
    public:
        struct Status
        {
            float maxHP;
            float HP;
            float maxMP;
            float MP;

            float attackDmg;
            float attackSpeed;

            float moveSpeed;
            eMoveType moveType;

            //Skill needed

            std::vector<float> buffVec[(UINT)eBuffType::End];

            Status() : maxHP{ 100.f }, HP{ 100.f }, maxMP{ 100.f }, MP{ 0.f }
                , attackDmg{ 10.f }, attackSpeed{ 1.f }, moveSpeed{ 5.f }, moveType{ eMoveType::Ground } {}

            Status(float hp, float MaxHP, float mp, float MaxMP, float AttackDmg, float AttackSpeed
                , float MoveSpeed, eMoveType MoveType)
                : maxHP{ MaxHP }, HP{ hp }, maxMP{ MaxMP }, MP{ mp }
                , attackDmg{ AttackDmg }, attackSpeed{ AttackSpeed }
                , moveSpeed{ MoveSpeed }, moveType{ MoveType } {}
        };


        BikerScript();
        ~BikerScript();

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

        void Start();
        void Action();
        void End();

    private:
        Transform* mOwnerTR;
        class Animator* mAnimator;

        bool mIdle;
        bool mRun;
        bool mDie;
        bool mAttack;
        bool mChange;

        Vector3 mPrevPos;
        float mMove;

        Status mStatus;
    };
}

