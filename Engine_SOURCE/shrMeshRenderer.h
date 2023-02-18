#pragma once
#include "shrBaseRenderer.h"

using namespace shr::graphics;
namespace shr
{

	class MeshRenderer : public BaseRenderer
	{
	public:
		MeshRenderer();
		virtual ~MeshRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;
	};

}