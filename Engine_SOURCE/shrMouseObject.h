#pragma once
#include "shrGameObject.h"

namespace shr
{
    class MouseObject :
        public GameObject
    {
    public:
		MouseObject();
		virtual ~MouseObject();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
		
    };
}

