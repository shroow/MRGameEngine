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

namespace shr
{
	TitleScene::TitleScene()
		: Scene(eSceneType::Title)
	{
	}

	TitleScene::~TitleScene()
	{
	}

	void TitleScene::Initialize()
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

	void TitleScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Play);
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
}
