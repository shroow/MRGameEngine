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

		static void SetPlayer(class PlayerObject* player) { mPlayer = player; }
		static void SetMouse(class MouseObject* mouse) { mMouse = mouse; }
		static void SetGoldUI(class NumUI* goldUI) { mGoldUI = goldUI; }
		static class PlayerObject* GetPlayer() { return mPlayer; }
		static class MouseObject* GetMouse() { return mMouse; }
		static class NumUI* GetGoldUI() { return mGoldUI; }

	private:
		static std::vector<Scene*> mSceneVec;
		static Scene* mActiveScene;

		static int mStageCount;
		static class PlayerObject* mPlayer;
		static class MouseObject* mMouse;
		static class NumUI* mGoldUI;
	};
}
