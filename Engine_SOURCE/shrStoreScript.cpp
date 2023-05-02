#include "shrStoreScript.h"
#include "shrSceneManager.h"
#include "shrBattleScene.h"
#include "shrStoreScene.h"
#include "shrPlayerObject.h"

namespace shr
{
	StoreScript::StoreScript()
		: Script(eScriptType::UnitScript)
		, mOwner(nullptr)
	{
	}
	StoreScript::~StoreScript()
	{
	}

	void StoreScript::Initialize()
	{
	}
	void StoreScript::Update()
	{
	}
	void StoreScript::Render()
	{
	}

	void StoreScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void StoreScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void StoreScript::OnCollisionExit(Collider2D* collider)
	{
	}
}
