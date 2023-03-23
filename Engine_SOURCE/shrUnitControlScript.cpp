#include "shrUnitControlScript.h"
#include "shrGameObject.h"
#include "shrMonsterScript.h"
#include "shrSceneManager.h"
#include "shrInput.h"
#include "shrTime.h"
#include "shrRenderer.h"
#include "shrCamera.h"

namespace shr
{
	UnitControlScript::UnitControlScript()
		: Script(eScriptType::ObjectScript)
		, mOwnerScripts{}
		, mbCusorOn(false)
		, mbControl(false)
	{
	}
	UnitControlScript::~UnitControlScript()
	{
		mOwnerScripts.clear();
	}

	void UnitControlScript::Initialize()
	{
		mOwnerScripts = GetOwner()->GetScriptVec();
	}
	void UnitControlScript::Update()
	{
		if (!mbCusorOn)
			return;

		if(Input::GetMouseLeftDown)
		{
			for (Script* script : mOwnerScripts)
			{
				if (script->GetScriptType() == eScriptType::UnitScript)
				{
					script->UnitSelected(true);
					mbControl = true;
				}
			}
		}

	}
	void UnitControlScript::Render()
	{
	}

	void UnitControlScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void UnitControlScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void UnitControlScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void UnitControlScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void UnitControlScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void UnitControlScript::OnTriggerExit(Collider2D* collider)
	{
	}
	void UnitControlScript::OnMouseCollisionEnter()
	{
		if (SceneManager::GetActiveScene()->GetSceneType() != eSceneType::Test)
			return;

		std::vector<Script*> scripts = GetOwner()->GetScriptVec();

		for (Script* script : scripts)
		{
			if (script->GetScriptType() == eScriptType::UnitScript)
			{
				script->UnitSelected(true);
				mbCusorOn = true;
			}
		}
	}
	void UnitControlScript::OnMouseCollisionStay()
	{
	}
	void UnitControlScript::OnMouseCollisionExit()
	{
		std::vector<Script*> scripts = GetOwner()->GetScriptVec();

		for (Script* script : scripts)
		{
			if (script->GetScriptType() == eScriptType::UnitScript)
			{
				script->UnitSelected(false);
				mbCusorOn = false;
			}
		}
	}
}