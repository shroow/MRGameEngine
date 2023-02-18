#pragma once
#include "shrScene.h"

namespace shr
{
	class SceneManager
	{
	public:
		static void Initialize();
		static void Update();
		static void FixedUpdate();
		static void Render();
		static void Release();

	private:
		static Scene* mPlayScene;
	};
}
