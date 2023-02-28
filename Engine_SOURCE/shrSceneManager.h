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

		static void LoadScene(eSceneType type);
		static Scene* GetActiveScene() { return mActiveScene; }

	private:
		static std::vector<Scene*> mSceneVec;
		static Scene* mActiveScene;
	};
}
