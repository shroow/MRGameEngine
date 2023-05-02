#include "shrBattleScene.h"

namespace shr
{
	BattleScene::BattleScene()
		: Scene(eSceneType::Battle)
		, mMainCamera(nullptr)
	{
	}

	BattleScene::~BattleScene()
	{
	}

	void BattleScene::Initialize()
	{
		Scene::Initialize();
	}

	void BattleScene::Update()
	{
		Scene::Update();
	}

	void BattleScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void BattleScene::Render()
	{
		Scene::Render();
	}

	void BattleScene::OnEnter()
	{
		Scene::OnEnter();
	}

	void BattleScene::OnExit()
	{
		Scene::OnExit();
	}

	void BattleScene::LoadResources()
	{
	}

	void BattleScene::CreateMonster(int num, Vector3 pos)
	{
	}
}