#include "shrMouseObject.h"
#include "shrInput.h"

namespace shr
{
	MouseObject::MouseObject()
		: GameObject()
		, mIsSelected(false)
		, mSelectedUnit(nullptr)
	{
	}
	MouseObject::~MouseObject()
	{
	}

	void MouseObject::Initialize()
	{
	}

	void MouseObject::Update()
	{
		GameObject::Update();
		Input::ComputeMousePos();

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = Input::GetMouseWorldPos();
		tr->SetPosition(Vector3(pos.x, pos.y, 1.f));


	}
	void MouseObject::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void MouseObject::Render()
	{
		GameObject::Render();
	}
}