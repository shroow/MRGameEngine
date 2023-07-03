#include "shrButtonUI.h"
#include "shrSpriteRenderer.h"
#include "shrResources.h"
#include "shrTexture.h"
#include "shrObject.h"
#include "shrInput.h"
#include "shrButtonScript.h"

namespace shr
{
	ButtonUI::ButtonUI()
		: UIBase()
		, mIsHovered(false)
		, mState(eButtonUIState::Idle)
		, mButtonScript(nullptr)
	{
		mButtonUICollider = AddComponent<Collider2D>();
		mButtonUICollider->SetType(eColliderType::Rect);
		mButtonScript = AddComponent<ButtonScript>();
	}

	ButtonUI::~ButtonUI()
	{
	}

	void ButtonUI::Initialize()
	{
		UIBase::Initialize();
	}

	void ButtonUI::Update()
	{
		UIBase::Update();
	}

	void ButtonUI::FixedUpdate()
	{
		UpdateState();

		UIBase::FixedUpdate();
	}

	void ButtonUI::Render()
	{
		std::shared_ptr<Material> mr = mUIRenderer->GetMaterial();

		if (mr != nullptr)
		{
			int state = (int)mState;

			mr->SetData(eGPUParam::Int_2, &state);
		}

		UIBase::Render();
	}

	void ButtonUI::UpdateState()
	{
		if (Input::GetMouseLeftDown())
		{
			if (mState == eButtonUIState::Hovered && mIsHovered)
				mState = eButtonUIState::Down;
		}
		else if (Input::GetMouseLeftPressed())
		{
			if (mState == eButtonUIState::Down)
				mState = eButtonUIState::Pressed;

			if (!mIsHovered)
				mState = eButtonUIState::Idle;
		}
		else if (Input::GetMouseLeftUp())
		{
			if (mIsHovered)
			{
				if (mState == eButtonUIState::Pressed || mState == eButtonUIState::Down)
				{
					if (mClickCallback)
						mClickCallback();
				}
			}
		}
	}
}
