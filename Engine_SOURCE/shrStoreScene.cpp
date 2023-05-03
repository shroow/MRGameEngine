#include "shrStoreScene.h"
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

#include "shrMouseScript.h"
#include "shrPlayerObject.h"
#include "shrPlayerScript.h"
#include "shrUnitObject.h"
#include "shrUnitScript.h"

namespace shr
{
	StoreScene::StoreScene()
		: Scene(eSceneType::Battle)
	{
	}

	StoreScene::~StoreScene()
	{
	}

	void StoreScene::Initialize()
	{
		LoadResources();

		// Main Camera Game Object
		mMainCamera = object::Instantiate<GameObject>(eLayerType::Camera);
		mMainCamera->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, 0.f));
		Camera* cameraComp = mMainCamera->AddComponent<Camera>();
		cameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		//cameraComp->RegisterCameraInRenderer();
		cameraComp->TurnLayerMask(eLayerType::SystemUI, false);
		mMainCamera->AddComponent<CameraScript>();
		mainCamera = cameraComp;

		//Directional Light
		{
			GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player);
			directionalLight->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -100.0f));
			Light* lightComp = directionalLight->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
			object::DontDestroyOnLoad(directionalLight);
		}

		//Timer
		{
			//타이머가 다떨어지면 상호작용을 해야되서 멤버로 들고 있어야됨
			//타이머숫자만큼 텍스처 렌더
		}

		//Player
		{
			PlayerObject* player = SceneManager::GetPlayer();
			player = object::Instantiate<PlayerObject>(eLayerType::Player);
			player->SetName(L"Player");

			Transform* tr = player->GetComponent<Transform>();
			tr->SetPosition(Vector3(-1.f, -1.f, 4.0f));
			tr->SetRotation(Vector3(0.f, 0.f, 0.f));
			tr->SetScale(Vector3(6.0f, 6.0f, 1.0f));

			player->SetPlayerState(ePlayerState::Store);

			PlayerScript* playerScript = player->GetPlayerScirpt();

			player->DontDestroy(true);
		}

		RerollStore();
	}

	void StoreScene::Update()
	{
		PlayerObject* player = SceneManager::GetPlayer();

		if (Input::GetKeyDown(eKeyCode::R))
		{
			if (player->SubGold(1))
				RerollStore();
		}

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

	void StoreScene::RerollStore()
	{
		PlayerObject* player = SceneManager::GetPlayer();
		int level = player->GetStoreLevel();

		for (int i = 0; i < level; ++i)
		{
			Vector3 pos(12.5f, 10.0f, 10.f);

			if (i < 3) {
				pos.x += i * 12.5f;
			}
			else if (i < 6) {
				pos.x += (i - 3) * 12.5f;
				pos.y -= 10.f;
			}
			else if (i < 10) {
				pos.x += (i - 6) * 12.5f;
				pos.y -= 20.f;
			}
			else
				break;

			//Random eUnitType
			//std::rand(
			/////////////////////////////

			CreateMonster(eUnitType::BallandChainBot, pos);
		}
	}

	void StoreScene::CreateMonster(eUnitType type, Vector3 pos)
	{

	}
}