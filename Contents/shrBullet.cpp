#include "shrBullet.h"

namespace shr
{
    Bullet::Bullet()
        : GameObject()
        , mLifeTime(0.f)
        , mDirection(Vector2::Zero)
        , mAnimator(nullptr)
    {
        mCollider = AddComponent<Collider2D>();
    }
    Bullet::Bullet(const Bullet& obj)
        : GameObject(obj)
        , mLifeTime(obj.mLifeTime)
        , mDirection(obj.mDirection)
        , mAnimator(nullptr)
    {
        mCollider = AddComponent<Collider2D>();
    }
    Bullet::~Bullet()
    {
    }

    void Bullet::Initialize()
    {
    }
    void Bullet::Update()
    {
        GameObject::Update();
    }
    void Bullet::FixedUpdate()
    {
        GameObject::FixedUpdate();
    }
    void Bullet::Render()
    {
        GameObject::Render();
    }
}