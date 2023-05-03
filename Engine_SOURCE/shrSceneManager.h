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
		static void Destroy();
		static void Release();

		static void LoadScene(eSceneType type);
		static Scene* GetActiveScene() { return mActiveScene; }

		static void SetStageCount(int count) { mStageCount = count; }
		static int GetStageCount() { return mStageCount; }
		static class PlayerObject* GetPlayer() { return mPlayer; }

	private:
		static std::vector<Scene*> mSceneVec;
		static Scene* mActiveScene;

		static int mStageCount;
		static class PlayerObject* mPlayer;
	};
}
