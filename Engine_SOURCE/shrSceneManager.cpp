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
#include "shrBikerScript.h"

#include "shrTitleScene.h"
#include "shrPlayScene.h"

namespace shr
{
	std::vector<Scene*> SceneManager::mSceneVec = {};
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Initialize()
	{
		mSceneVec.resize((UINT)eSceneType::End);

		mSceneVec[(UINT)eSceneType::Tilte] = new TitleScene();
		mSceneVec[(UINT)eSceneType::Play] = new PlayScene();
		
		mActiveScene = mSceneVec[(UINT)eSceneType::Tilte];

		for (Scene* scene : mSceneVec)
		{
			scene->Initialize();
		}
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

		//dontDestroyObject들 넘겨주기
		std::vector<GameObject*> gameObjs
			= mActiveScene->GetDontDestroyGameObjects();
		mActiveScene = mSceneVec[(UINT)type];

		for (GameObject* obj : gameObjs)
		{
			eLayerType type = obj->GetLayerType();
			mActiveScene->AddGameObject(obj, type);
		}

		mActiveScene->OnEnter();
	}
}