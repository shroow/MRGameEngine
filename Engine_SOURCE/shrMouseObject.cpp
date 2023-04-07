#include "shrMouseObject.h"
#include "shrInput.h"

namespace shr
{
	MouseObject::MouseObject()
		: GameObject()
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
	}
	void MouseObject::FixedUpdate()
	{
		Input::ComputeMousePos();
	}
	void MouseObject::Render()
	{
	}
}