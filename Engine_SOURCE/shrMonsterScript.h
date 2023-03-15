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
        float mHP;
        float mMaxHP;
        float mMP;
        float mMaxMP;
        bool mIdle;
        bool mMove;
        bool mDie;
        bool mAttack;
        bool mChange;
    };
}

