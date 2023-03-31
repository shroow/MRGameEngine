#include "shrMouseScript.h"
#include "shrTransform.h"
#include "shrGameObject.h"
#include "shrInput.h"
#include "shrTime.h"

namespace shr
{
	MouseScript::MouseScript()
		: Script(eScriptType::ObjectScript)
	{
	}

	MouseScript::~MouseScript()
	{
	}

	void MouseScript::Initialize()
	{
	}

	void MouseScript::Update()
	{
	}

	void MouseScript::FixedUpdate()
	{
		Input::ComputeMousePos();
	}

	void MouseScript::Render()
	{
	}
}