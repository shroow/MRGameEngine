#include "shrButtonScript.h"
#include "shrButtonUI.h"

namespace shr
{
	ButtonScript::ButtonScript()
		: Script(eScriptType::ObjectScript)
	{
	}

	ButtonScript::~ButtonScript()
	{
	}

	void ButtonScript::Initialize()
	{
	}

	void ButtonScript::Update()
	{
	}

	void ButtonScript::FixedUpdate()
	{
	}

	void ButtonScript::Render()
	{
	}

	void ButtonScript::OnCollisionEnter(Collider2D* collider)
	{
	}

	void ButtonScript::OnCollisionStay(Collider2D* collider)
	{
	}

	void ButtonScript::OnCollisionExit(Collider2D* collider)
	{
	}

	void ButtonScript::OnTriggerEnter(Collider2D* collider)
	{
	}

	void ButtonScript::OnTriggerStay(Collider2D* collider)
	{
	}

	void ButtonScript::OnTriggerExit(Collider2D* collider)
	{
	}

	void ButtonScript::OnMouseCollisionEnter()
	{
		ButtonUI* owner = dynamic_cast<ButtonUI*>(GetOwner());

		if (owner != nullptr)
		{
			owner->SetHovered(true);
			owner->SetState(eButtonUIState::Hovered);
		}
		else
			assert(false);
	}

	void ButtonScript::OnMouseCollisionStay()
	{
	}

	void ButtonScript::OnMouseCollisionExit()
	{
		ButtonUI* owner = dynamic_cast<ButtonUI*>(GetOwner());

		if (owner != nullptr)
		{
			owner->SetHovered(false);
			owner->SetState(eButtonUIState::Idle);
		}
		else
			assert(false);
	}
}
