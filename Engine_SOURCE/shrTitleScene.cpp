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
#include "shrPlayer.h"
#include "shrMonster.h"
#include "shrCollisionManager.h"
#include "shrAnimator.h"
#include "shrLight.h"
#include "shrPaintShader.h"
#include "shrUnitScript.h"
#include "shrParticleSystem.h"

namespace shr
{
	TitleScene::TitleScene()
		: Scene(eSceneType::Title)
		, mMainCamera(nullptr)
	{
	}

	TitleScene::~TitleScene()
	{
	}

	void TitleScene::Initialize()
	{
		Scene::Initialize();
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
	void TitleScene::CreateMonster(int num, Vector3 pos)
	{
	}
}
