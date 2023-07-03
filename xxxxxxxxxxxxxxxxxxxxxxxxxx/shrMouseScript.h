#pragma once
#include "shrScript.h"

namespace shr
{
    class MouseScript :
        public Script
    {
		public:
		MouseScript();
		~MouseScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

	private:
		Vector2 mWorldPos;
    };
}

