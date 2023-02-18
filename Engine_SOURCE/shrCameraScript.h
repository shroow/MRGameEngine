#pragma once
#include "shrScript.h"

namespace shr
{
	class CameraScript
		: public Script
	{
	public:
		CameraScript();
		~CameraScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;

	private:

	};
}
