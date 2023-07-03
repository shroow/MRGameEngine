#pragma once
#include "shrGameObject.h"
#include "shrAnimator.h"
namespace shr
{
    class Skill :
        public GameObject
    {
    public:
        Skill();
        Skill(eSkillType type);
        Skill(const Skill& obj);
        virtual ~Skill();

        virtual void Initialize();
        virtual void Update();
        virtual void FixedUpdate();
        virtual void Render();

        bool SetSkillAnimation();

        float GetLifeTime() { return mLifeTime; }
        Vector2 GetDirection() { return mDirection; }
        Collider2D* GetCollider() { return mCollider; }
        class Animator* GetAnimator() { return mAnimator; }

        void SetLifeTime(float time) { mLifeTime = time; }
        void SetDirection(Vector2 dir) { mDirection = dir; }
        void SetCollider(Collider2D* collider) { mCollider = collider; }
        void SetAnimator(class Animator* animator) { mAnimator = animator; }

    protected:
        float mLifeTime;
        Vector2 mDirection;
        Collider2D* mCollider;
        class Animator* mAnimator;

    private:
        eSkillType mSkillType;
    };
}

