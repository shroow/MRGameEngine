#pragma once
#include "shrGameObject.h"

namespace shr
{
    class Bullet :
        public GameObject
    {
    public:
        Bullet();
        Bullet(const Bullet& obj);
        virtual ~Bullet();

        virtual void Initialize();
        virtual void Update();
        virtual void FixedUpdate();
        virtual void Render();


        float GetLifeTime() { return mLifeTime; }
        Vector2 GetDirection() { return mDirection; }
        Collider2D* GetCollider() { return mCollider; }
        class Animator* GetAnimator() { return mAnimator; }

    private:
        float mLifeTime;
        Vector2 mDirection;
        Collider2D* mCollider;
        class Animator* mAnimator;
    };
}

