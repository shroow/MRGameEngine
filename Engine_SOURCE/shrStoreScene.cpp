#include "shrStoreScene.h"

namespace shr
{
	StoreScene::StoreScene()
		: Scene(eSceneType::Battle)
		, mMainCamera(nullptr)
	{
	}

	StoreScene::~StoreScene()
	{
	}

	void StoreScene::Initialize()
	{
		Scene::Initialize();
	}

	void StoreScene::Update()
	{
		Scene::Update();
	}

	void StoreScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void StoreScene::Render()
	{
		Scene::Render();
	}

	void StoreScene::OnEnter()
	{
		Scene::OnEnter();
	}

	void StoreScene::OnExit()
	{
		Scene::OnExit();
	}

	void StoreScene::LoadResources()
	{
	}

	void StoreScene::CreateMonster(int num, Vector3 pos)
	{
	}
}