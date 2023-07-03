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
#include "shrBackgroundScene.h"
#include "shrStageSelectScene.h"

#include "shrObject.h"
#include "shrMouseScript.h"
#include "shrPlayerObject.h"
#include "shrSceneInfo.h"
#include "shrCollisionManager.h"
#include "shrNumUI.h"

namespace shr
{
	std::vector<Scene*> SceneManager::mSceneVec = {};
	Scene* SceneManager::mActiveScene = nullptr;
	int SceneManager::mStageCount = 0;
	PlayerObject* SceneManager::mPlayer = nullptr;
	MouseObject* SceneManager::mMouse = nullptr;
	NumUI* SceneManager::mGoldUI = nullptr;

	void SceneManager::Initialize()
	{
		mSceneVec.resize((UINT)eSceneType::End);

		mSceneVec[(UINT)eSceneType::Background] = new BackgroundScene();
		mSceneVec[(UINT)eSceneType::Test] = new TestScene();
		mSceneVec[(UINT)eSceneType::Title] = new TitleScene();
		mSceneVec[(UINT)eSceneType::StageSelect] = new StageSelectScene();
		mSceneVec[(UINT)eSceneType::Play] = new PlayScene();
		mSceneVec[(UINT)eSceneType::Store] = new StoreScene();
		mSceneVec[(UINT)eSceneType::Battle] = new BattleScene();

		mActiveScene = mSceneVec[(UINT)eSceneType::Title];

		//for (Scene* scene : mSceneVec)
		//{
		//	scene->Initialize();
		//}

		SceneInfo::LoadResourcesInfo();

		mSceneVec[(UINT)eSceneType::Background]->Start();
		mSceneVec[(UINT)eSceneType::Background]->Initialize();

		mActiveScene->Start();
		mActiveScene->Initialize();
		mainCamera = mActiveScene->GetMainCamera()->GetComponent<Camera>();


		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Enemy);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Background);
		CollisionManager::CollisionLayerCheck(eLayerType::Monster, eLayerType::Background);

		CollisionManager::MouseCollisionLayerCheck(eLayerType::Player);
		CollisionManager::MouseCollisionLayerCheck(eLayerType::Enemy);
		CollisionManager::MouseCollisionLayerCheck(eLayerType::Monster);
		CollisionManager::MouseCollisionLayerCheck(eLayerType::SystemUI);
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
		{
			mActiveScene->OnExit();
		}

		Scene* mPrevScene = mActiveScene;

		// 바뀔때 dontDestory 오브젝트는 다음씬으로 같이 넘겨줘야한다.
		std::vector<GameObject*> gameObjs
			= mActiveScene->GetDontDestroyGameObjects();

		mActiveScene = mSceneVec[(UINT)type];
		mSceneVec[(UINT)type]->Initialize();

		for (GameObject* obj : gameObjs)
		{
			eLayerType type = obj->GetLayerType();
			mActiveScene->AddGameObject(obj, type);
		}


		mainCamera = mActiveScene->GetMainCamera()->GetComponent<Camera>();

		mActiveScene->OnEnter();
	}
}