#include "shrSceneManager.h"
#include "shrResources.h"
#include "shrTexture.h"
#include "shrInput.h"

#include "shrCamera.h"
#include "shrTransform.h"

#include "shrRenderer.h"
#include "shrSpriteRenderer.h"
#include "shrMeshRenderer.h"

#include "shrCameraScript.h"
#include "shrGridScript.h"
#include "shrFadeInScript.h"
#include "shrPlayerScript.h"

#include "shrTitleScene.h"
#include "shrPlayScene.h"
#include "shrTestScene.h"
#include "shrStoreScene.h"
#include "shrBattleScene.h"

#include "shrObject.h"
#include "shrMouseScript.h"

namespace shr
{
	std::vector<Scene*> SceneManager::mSceneVec = {};
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Initialize()
	{
		mSceneVec.resize((UINT)eSceneType::End);

		mSceneVec[(UINT)eSceneType::Test] = new TestScene();
		mSceneVec[(UINT)eSceneType::Title] = new TitleScene();
		mSceneVec[(UINT)eSceneType::Play] = new PlayScene();
		mSceneVec[(UINT)eSceneType::Store] = new StoreScene();
		mSceneVec[(UINT)eSceneType::Battle] = new BattleScene();

		mActiveScene = mSceneVec[(UINT)eSceneType::Test];

		//for (Scene* scene : mSceneVec)
		//{
		//	scene->Initialize();
		//}

		mActiveScene->Initialize();
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
	}

	void SceneManager::FixedUpdate()
	{
		mActiveScene->FixedUpdate();
	}

	void SceneManager::Render()
	{
		mActiveScene->Render();
	}

	void SceneManager::Destroy()
	{
		mActiveScene->Destroy();
	}

	void SceneManager::Release()
	{
		for (Scene* scene : mSceneVec)
		{
			delete scene;
			scene = nullptr;
		}
	}
	void SceneManager::LoadScene(eSceneType type)
	{
		if (mActiveScene)
			mActiveScene->OnExit();

		mSceneVec[(UINT)type]->Initialize();

		// 바뀔때 dontDestory 오브젝트는 다음씬으로 같이 넘겨줘야한다.
		std::vector<GameObject*> gameObjs
			= mActiveScene->GetDontDestroyGameObjects();
		mActiveScene = mSceneVec[(UINT)type];

		for (GameObject* obj : gameObjs)
		{
			eLayerType type = obj->GetLayerType();
			mActiveScene->AddGameObject(obj, type);
		}

		mainCamera = mActiveScene->GetMainCamera();

		mActiveScene->OnEnter();
	}
}