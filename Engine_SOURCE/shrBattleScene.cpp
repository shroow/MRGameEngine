#include "shrBattleScene.h"
#include "shrResources.h"
#include "shrSceneManager.h"
#include "shrInput.h"
#include "shrCamera.h"
#include "shrCameraScript.h"
#include "shrObject.h"
#include "shrGameObject.h"
#include "shrSpriteRenderer.h"
#include "shrAnimator.h"
#include "shrCollisionManager.h"
#include "shrParticleSystem.h"
#include "shrPaintShader.h"

#include "shrMouseObject.h"
#include "shrMouseScript.h"
#include "shrPlayerObject.h"
#include "shrPlayerScript.h"
#include "shrUnitObject.h"
#include "shrUnitScript.h"
#include "shrNumUI.h"

namespace shr
{
	BattleScene::BattleScene()
		: Scene(eSceneType::Battle)
		, mEnemy(nullptr)
	{
	}

	BattleScene::~BattleScene()
	{
		if(mEnemy != nullptr)
			mEnemy->ClearDeck();
	}

	void BattleScene::Start()
	{
	}

	void BattleScene::Initialize()
	{
		//LoadResources();

		// Main Camera Game Object
		mMainCamera = object::Instantiate<GameObject>(eLayerType::Camera);
		mMainCamera->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, 0.f));
		Camera* cameraComp = mMainCamera->AddComponent<Camera>();
		cameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		//cameraComp->RegisterCameraInRenderer();
		cameraComp->TurnLayerMask(eLayerType::SystemUI, true);
		//mMainCamera->AddComponent<CameraScript>();
		//mainCamera = cameraComp;

		//Enemy
		{
			mEnemy = object::Instantiate<PlayerObject>(eLayerType::Player);
			mEnemy->SetName(L"Enemy");

			Transform* tr = mEnemy->GetComponent<Transform>();
			tr->SetPosition(Vector3(1.f, 1.f, 4.0f));
			tr->SetRotation(Vector3(0.f, 0.f, 0.f));
			tr->SetScale(Vector3(6.0f, 6.0f, 1.0f));

			mEnemy->SetPlayerState(ePlayerType::Store);

			PlayerScript* playerScript = mEnemy->GetPlayerScirpt();
		}

		//Enemy Monster
		{
			{
				UnitObject* obj = object::Instantiate<UnitObject>(eLayerType::Monster2);
				obj->SetCharType(eUnitType::BallandChainBot);
				Transform* tr = obj->GetComponent<Transform>();
				tr->SetPosition(Vector3(12.5f, 10.0f, 10.f));
				tr->SetRotation(Vector3(0.f, 0.f, 0.f));
				tr->SetScale(Vector3(6.0f, 6.0f, 1.0f));

				//Animation add(using script)
				UnitScript* monScript = obj->GetScript<UnitScript>();
				{
					monScript->LoadUnitAnim(eUnitType::BallandChainBot);
				}
				monScript->PlayUnitAnim(eUnitState::Idle);

				mEnemy->AddUnit(obj);
			}

			{
				UnitObject* obj = object::Instantiate<UnitObject>(eLayerType::Monster2);
				obj->SetCharType(eUnitType::BallandChainBot);
				Transform* tr = obj->GetComponent<Transform>();
				tr->SetPosition(Vector3(25.0f, 0.0f, 10.f));
				tr->SetRotation(Vector3(0.f, 0.f, 0.f));
				tr->SetScale(Vector3(6.0f, 6.0f, 1.0f));

				//Animation add(using script)
				UnitScript* monScript = obj->GetScript<UnitScript>();
				{
					monScript->LoadUnitAnim(eUnitType::BallandChainBot);
				}
				monScript->PlayUnitAnim(eUnitState::Idle);

				mEnemy->AddUnit(obj);
			}

			{
				UnitObject* obj = object::Instantiate<UnitObject>(eLayerType::Monster2);
				obj->SetCharType(eUnitType::BallandChainBot);
				Transform* tr = obj->GetComponent<Transform>();
				tr->SetPosition(Vector3(12.5f, -10.0f, 10.f));
				tr->SetRotation(Vector3(0.f, 0.f, 0.f));
				tr->SetScale(Vector3(6.0f, 6.0f, 1.0f));

				//Animation add(using script)
				UnitScript* monScript = obj->GetScript<UnitScript>();
				{
					monScript->LoadUnitAnim(eUnitType::BallandChainBot);
				}
				monScript->PlayUnitAnim(eUnitState::Idle);

				mEnemy->AddUnit(obj);
			}
		}
	}

	void BattleScene::Update()
	{
		PlayerObject* player = SceneManager::GetPlayer();
		NumUI* goldUI = SceneManager::GetGoldUI();

		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Store);
		}

		if (Input::GetKeyDown(eKeyCode::B))
		{
			Battle();
		}

		UINT gold = player->GetGold();
		goldUI->SetNum(gold);

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

		//GetEnemey();

	}

	void BattleScene::OnExit()
	{
		Scene::OnExit();


		mEnemy->ClearDeck();

		PlayerObject* player = SceneManager::GetPlayer();
		player->EndBattle();

		Layer& layer = GetLayer(eLayerType::Monster);
		Layer& layer2 = GetLayer(eLayerType::Monster2);

		layer.OnExit();
		layer2.OnExit();
	}

	void BattleScene::Battle()
	{
		PlayerObject* player = SceneManager::GetPlayer();

		player->Battle(mEnemy);

		mEnemy->Battle(player);
	}

	void BattleScene::GetEnemy()
	{

	}

	void BattleScene::LoadResources()
	{
	}

	void BattleScene::CreateMonster(eUnitType type, Vector3 pos)
	{
	}
}