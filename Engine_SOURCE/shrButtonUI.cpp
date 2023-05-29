#include "shrButtonUI.h"
#include "shrSpriteRenderer.h"
#include "shrResources.h"
#include "shrTexture.h"
#include "shrObject.h"

namespace shr
{
	ButtonUI::ButtonUI()
		: mHovered(false)
		, mClicked(false)
		, mSprite(nullptr)
	{
	}
	ButtonUI::ButtonUI(const ButtonUI& obj)
		: mHovered(obj.mHovered)
		, mClicked(obj.mClicked)
		, mSprite(nullptr)
	{
	}
	ButtonUI::~ButtonUI()
	{
	}
	void ButtonUI::Initialize()
	{
	}
	void ButtonUI::Update()
	{
		GameObject::Update();

		if (mSprite == nullptr)
			return;

		std::shared_ptr<Material> mr = mSprite->GetMaterial();

		if(mr != nullptr)
		{
			std::shared_ptr<Shader> shader =  mr->GetShader();
		}
	}
	void ButtonUI::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void ButtonUI::Render()
	{
		GameObject::Render();
	}
}
