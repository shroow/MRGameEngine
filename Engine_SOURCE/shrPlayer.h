#pragma once
#include "shrGameObject.h"

namespace shr
{
    class Player :
        public GameObject
    {
	public:
		Player();
		virtual ~Player();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
    };
}

