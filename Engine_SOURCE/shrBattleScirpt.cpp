#include "shrBattleScirpt.h"
#include "shrSceneManager.h"
#include "shrBattleScene.h"
#include "shrStoreScene.h"
#include "shrPlayerObject.h"

namespace shr
{
	BattleScirpt::BattleScirpt()
		: Script(eScriptType::UnitScript)
		, mOwner(nullptr)
	{
	}
	BattleScirpt::~BattleScirpt()
	{
	}

	void BattleScirpt::Initialize()
	{
	}
	void BattleScirpt::Update()
	{
	}
	void BattleScirpt::Render()
	{
	}

	void BattleScirpt::OnCollisionEnter(Collider2D* collider)
	{
	}
	void BattleScirpt::OnCollisionStay(Collider2D* collider)
	{
	}
	void BattleScirpt::OnCollisionExit(Collider2D* collider)
	{
	}
}
