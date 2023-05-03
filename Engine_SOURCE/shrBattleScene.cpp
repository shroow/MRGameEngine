#include "shrBattleScene.h"

namespace shr
{
	BattleScene::BattleScene()
		: Scene(eSceneType::Battle)
	{
	}

	BattleScene::~BattleScene()
	{
	}

	void BattleScene::Initialize()
	{
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