#include "shrScript.h"

namespace shr
{
	Script::Script(eScriptType scriptType)
		: Component(eComponentType::Script)
		, mScriptType(scriptType)
	{
	}
	Script::~Script()
	{
	}
	void Script::Initialize()
	{
	}
	void Script::Update()
	{
	}
	void Script::FixedUpdate()
	{
	}
	void Script::Render()
	{
	}
}