#pragma once
#include "shrBaseRenderer.h"

using namespace shr::graphics;
namespace shr
{
    class SpriteRenderer :
        public BaseRenderer
    {
	public:
		SpriteRenderer();
		virtual ~SpriteRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;
    };
}
