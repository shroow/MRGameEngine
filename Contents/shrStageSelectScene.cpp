#include "shrStageSelectScene.h"
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
#include "shrPlayerObject.h"
#include "shrUnitObject.h"
#include "shrBaseWidgetUI.h"

#include "shrMouseScript.h"
#include "shrPlayerScript.h"
#include "shrUnitScript.h"

#include "shrSceneInfo.h"
#include "shrNumUI.h"

namespace shr
{
	StageSelectScene::StageSelectScene()
		:Scene(eSceneType::StageSelect)
		, mBackground(nullptr)
	{
	}
	StageSelectScene::~StageSelectScene()
	{
	}

	void StageSelectScene::Start()
	{
		//Setting etc ButtonUI
		{

		}
	}
	void StageSelectScene::Initialize()
	{
		LoadResources();

		// Main Camera Game Object
		mMainCamera = object::Instantiate<GameObject>(eLayerType::Camera);
		mMainCamera->SetName(L"StoreSceneCamera");
		mMainCamera->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, 0.f));
		Camera* cameraComp = mMainCamera->AddComponent<Camera>();
		cameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		//cameraComp->RegisterCameraInRenderer();
		cameraComp->TurnLayerMask(eLayerType::SystemUI, true);
		//mMainCamera->AddComponent<CameraScript>();
		//mainCamera = cameraComp;

		//Background
		{
			mBackground = object::Instantiate<GameObject>(eLayerType::Background);
			mBackground->SetName(L"StageBackground");
			Transform* tr = mBackground->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.f, 0.f, 998.f));
			tr->SetScale(Vector3(128.0f, 72.0f, 1.f));

			SpriteRenderer* sr = mBackground->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> material = std::make_shared<Material>();
			std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"StageBackground_Texture");
			std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"RectShader");

			material->SetRenderingMode(eRenderingMode::Transparent);
			material->SetTexture(eTextureSlot::T0, texture);
			material->SetShader(shader);

			Resources::Insert<Material>(L"StageBackground_Material", material);

			sr->SetMaterial(material);
			sr->SetMesh(mesh);
		}

		//Stage UI
		{
			//PlayerDeck Detail WidgetUI
			{
				BaseWidgetUI* obj = object::Instantiate<BaseWidgetUI>(eLayerType::SystemUI);
				obj->SetName(L"PlayerDeck_Detail_WidgetUI");
				Transform* tr = obj->GetComponent<Transform>();
				tr->SetPosition(Vector3(0.f, -28.f, 1.9f));
				tr->SetScale(Vector3(45.7f, 18.5f, 1.f));
				tr->SetRotation(Vector3(0.f, 0.f, 0.f));

				//obj->AddUI()
			}

			//Current Stage WidgetUI
			{
				BaseWidgetUI* obj = object::Instantiate<BaseWidgetUI>(eLayerType::SystemUI);
				obj->SetName(L"Current Stage WidgetUI");
				Transform* tr = obj->GetComponent<Transform>();
				tr->SetPosition(Vector3(0.f, 30.f, 1.9f));
				tr->SetScale(Vector3(16.6f, 11.0f, 1.f));
				tr->SetRotation(Vector3(0.f, 0.f, 180.f));

				//obj->AddUI()
			}
		}

		//Selectable Stage Object
		{

		}

	}
	void StageSelectScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Store);
		}

		Scene::Update();
	}
	void StageSelectScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}
	void StageSelectScene::Render()
	{
		Scene::Render();
	}

	void StageSelectScene::OnEnter()
	{
	}
	void StageSelectScene::OnExit()
	{
	}

	void StageSelectScene::LoadResources()
	{
		Resources::Load<Texture>(L"StageBackground_Texture"
			, L"Background\\TileSet\\ForestTileRoad.png");
	}
}