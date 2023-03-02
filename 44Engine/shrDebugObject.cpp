#include "shrDebugObject.h"

namespace shr
{
	DebugObject::DebugObject()
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