#include "shrStatusComponent.h"

namespace shr
{
	StatusComponent::StatusComponent()
		: Component(eComponentType::Status)
		, mStatus{}
	{
	}

	StatusComponent::~StatusComponent()
	{
	}

	void StatusComponent::Initialize()
	{
		mStatus = Status{};
	}

	void StatusComponent::Update()
	{
	}
	void StatusComponent::FixedUpdate()
	{
	}

	void StatusComponent::Render()
	{
	}
}
