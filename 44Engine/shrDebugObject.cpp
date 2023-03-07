#include "shrDebugObject.h"

namespace shr
{
	DebugObject::DebugObject()
		: GameObject()
	{
	}

	DebugObject::~DebugObject()
	{
	}

	void DebugObject::FixedUpdate()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->FixedUpdate();
		}
	}
}