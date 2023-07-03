#include "shrTitleScene.h"
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
#include "shrCollider2D.h"
#include "shrCollisionManager.h"
#include "shrAnimator.h"
#include "shrLight.h"
#include "shrPaintShader.h"
#include "shrUnitScript.h"
#include "shrParticleSystem.h"
#include "shrPlayerObject.h"
#include "shrMouseObject.h"
#include "shrButtonUI.h"
#include "shrApplication.h"

extern shr::Application application;

namespace shr
{
	TitleScene::TitleScene()
		: Scene(eSceneType::Title)
	{
	}

	TitleScene::~TitleScene()
	{
	}

	void TitleScene::Start()
	{
		Scene::Start();

		//Static
		{
			//Player
			{
				PlayerObject* player = object::Instantiate<PlayerObject>(eLayerType::Player);
				player->SetName(L"Player");

				Transform* tr = player->GetComponent<Transform>();
				tr->SetPosition(Vector3(-1.f, -1.f, 4.0f));
				tr->SetRotation(Vector3(0.f, 0.f, 0.f));
				tr->SetScale(Vector3(6.0f, 6.0f, 1.0f));

				player->SetPlayerState(ePlayerType::Player);
				PlayerScript* playerScript = player->GetPlayerScirpt();

				player->DontDestroy(true);
				SceneManager::SetPlayer(player);
			}
			//Mouse
			{
				MouseObject* mouse = object::Instantiate<MouseObject>(eLayerType::Mouse);
				mouse->SetName(L"Mouse");
				mouse->DontDestroy(true);
				SceneManager::SetMouse(mouse);
			}
		}
	}

	void TitleScene::Initialize()
	{
		//MainCamera
		mMainCamera = object::Instantiate<GameObject>(eLayerType::Camera);
		mMainCamera->SetName(L"TitleSceneCamera");
		mMainCamera->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, 0.f));
		Camera* cameraComp = mMainCamera->AddComponent<Camera>();
		cameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		//cameraComp->RegisterCameraInRenderer();
		cameraComp->TurnLayerMask(eLayerType::SystemUI, true);
		//mMainCamera->AddComponent<CameraScript>();
		mainCamera = cameraComp;

		//Start Button
		{
			ButtonUI* obj = object::Instantiate<ButtonUI>(eLayerType::SystemUI);
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(-10.f, -15.f, 3.f));
			tr->SetScale(Vector3(10.f, 3.f, 1.f));

			SpriteRenderer* sr = obj->GetRenderer();
			std::shared_ptr mr = Resources::Find<Material>(L"StartButton_Material");
			sr->SetMaterial(mr);

			obj->SetClickCallback(this, &TitleScene::StartGame);
		}

		//Setting Button
		{
			ButtonUI* obj = object::Instantiate<ButtonUI>(eLayerType::SystemUI);
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(1.f, -15.f, 3.f));
			tr->SetScale(Vector3(10.f, 3.f, 1.f));

			SpriteRenderer* sr = obj->GetRenderer();
			std::shared_ptr mr = Resources::Find<Material>(L"SettingButton_Material");
			sr->SetMaterial(mr);

			obj->SetClickCallback(this, &TitleScene::SettingOpen);
		}

		//Quit Button
		{
			ButtonUI* obj = object::Instantiate<ButtonUI>(eLayerType::SystemUI);
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(9.f, -15.f, 3.f));
			tr->SetScale(Vector3(4.f, 3.f, 1.f));

			SpriteRenderer* sr = obj->GetRenderer();
			std::shared_ptr mr = Resources::Find<Material>(L"QuitButton_Material");
			sr->SetMaterial(mr);

			obj->SetClickCallback(this, &TitleScene::QuitGame);
		}
	}

	void TitleScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Store);
		}

		Scene::Update();
	}
	void TitleScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}
	void TitleScene::Render()
	{
		Scene::Render();
	}
	void TitleScene::OnEnter()
	{
		Initialize();
	}
	void TitleScene::OnExit()
	{
		Scene::Destroy();
	}
	void TitleScene::LoadResources()
	{
	}

	void TitleScene::StartGame()
	{
		SceneManager::LoadScene(eSceneType::StageSelect);
	}
	void TitleScene::SettingOpen()
	{
		SceneManager::LoadScene(eSceneType::Setting);
	}
	void TitleScene::QuitGame()
	{
		HWND hWnd = application.GetHwnd();
		if (hWnd)
			DestroyWindow(hWnd);
	}
}
