#include "shrSkill.h"
#include "shrTexture.h"

namespace shr
{
	Skill::Skill()
		: GameObject()
		, mSkillType(eSkillType::None)
		, mLifeTime(0.f)
		, mDirection(Vector2::Zero)
		, mAnimator(nullptr)
	{
		mCollider = AddComponent<Collider2D>();
		mAnimator = AddComponent<Animator>();
	}
	Skill::Skill(eSkillType type)
		: GameObject()
		, mSkillType(type)
		, mLifeTime(0.f)
		, mDirection(Vector2::Zero)
		, mAnimator(nullptr)
	{
		mCollider = AddComponent<Collider2D>();
		mAnimator = AddComponent<Animator>();
	}

	Skill::Skill(const Skill& obj)
		: GameObject(obj)
		, mSkillType(obj.mSkillType)
		, mLifeTime(obj.mLifeTime)
		, mDirection(obj.mDirection)
		, mAnimator(nullptr)
	{
		mCollider = AddComponent<Collider2D>();
		mAnimator = AddComponent<Animator>();
	}
	Skill::~Skill()
	{
	}

	void Skill::Initialize()
	{
	}
	void Skill::Update()
	{
		GameObject::Update();
	}
	void Skill::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Skill::Render()
	{
		GameObject::Render();
	}

	bool Skill::SetSkillAnimation()
	{
		return false;
	}
}