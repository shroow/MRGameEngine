#pragma once
#include "shrGameObject.h"

namespace shr
{
    class Monster :
        public GameObject
    {
	public:
		Monster();
		virtual ~Monster();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:

    };
}

