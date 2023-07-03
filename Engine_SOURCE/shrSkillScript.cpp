#include "shrSkillScript.h"

namespace shr
{
	SkillScript::SkillScript()
		: Script(eScriptType::UnitScript)
		, mAnimator(nullptr)
		, mTransform(nullptr)
		, mEnemy(nullptr)
		, mOwner(nullptr)
		, mbStartMove(false)
		, mMovetoPos{}
		, mSelectedPos{}
		, mPrevPos{}
		, mMove(0.f)
		, mMoveDir{}
		, mIsDirLeft(false)
	{
	}
	SkillScript::~SkillScript()
	{
	}
	void SkillScript::Initialize()
	{
	}
	void SkillScript::Update()
	{
	}
	void SkillScript::FixedUpdate()
	{
	}
	void SkillScript::Render()
	{
	}
	void SkillScript::Move()
	{
	}
	void SkillScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void SkillScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void SkillScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void SkillScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void SkillScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void SkillScript::OnTriggerExit(Collider2D* collider)
	{
	}
	void SkillScript::OnMouseCollisionEnter()
	{
	}
	void SkillScript::OnMouseCollisionStay()
	{
	}
	void SkillScript::OnMouseCollisionExit()
	{
	}
	void SkillScript::SetSkillAnim(eUnitType type)
	{
	}
	void SkillScript::LoadSkillAnim(eUnitType type)
	{
	}
	void SkillScript::LoadSkillAnim(eUnitState animState, Vector2 offset, Vector2 leftTop, Vector2 spriteSize, UINT spriteLength, float duration, eAtlasType atlasType)
	{
	}
	void SkillScript::Start()
	{
	}
	void SkillScript::Action()
	{
	}
	void SkillScript::End()
	{
	}
	void SkillScript::AttackComplete()
	{
	}
	void SkillScript::SkillActive()
	{
	}
}