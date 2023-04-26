#pragma once
#include "shrGameObject.h"

namespace shr
{
    class UnitUI :
        public GameObject
    {
	public:
		UnitUI();
		virtual ~UnitUI();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
		GameObject* mHPBar;
		GameObject* mMPBar;
    };
}

