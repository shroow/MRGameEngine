#include "shrPlayScene.h"
#include "shrTransform.h"
#include "shrMeshRenderer.h"
#include "shrRenderer.h"
#include "shrResources.h"
#include "shrTexture.h"
#include "shrPlayerScript.h"
#include "shrCamera.h"
#include "shrCameraScript.h"
#include "shrSpriteRenderer.h"
#include "shrGridScript.h"
#include "shrObject.h"
#include "shrInput.h"
#include "shrCollisionManager.h"
#include "shrPlayer.h"
#include "shrMonster.h"
#include "shrPlayerScript.h"
#include "shrUnitScript.h"
#include "shrCollider2D.h"

namespace shr
{
	PlayScene::PlayScene()
		: Scene(eSceneType::Play)
		, mMainCamera(nullptr)
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		LoadResources();

		Scene::Initialize();

		return;
	}
	void PlayScene::Update()
	{	
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Test);
		}
	}
	void PlayScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}
	void PlayScene::Render()
	{
		Scene::Render();
	}
	void PlayScene::OnEnter()
	{
		Scene::OnEnter();
	}
	void PlayScene::OnExit()
	{
		Scene::OnExit();
	}
	void PlayScene::LoadResources()
	{
	}
	void PlayScene::CreateMonster(int num, Vector3 pos)
	{
	}
}