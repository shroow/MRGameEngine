#include "shrBackgroundScene.h"
#include "shrObject.h"
#include "shrTexture.h"
#include "shrResources.h"
#include "shrCamera.h"
#include "shrSpriteRenderer.h"
#include "shrApplication.h"

extern shr::Application application;

namespace shr
{
	BackgroundScene::BackgroundScene()
		: Scene(eSceneType::Background)
		, mBackground(nullptr)
	{
	}
	BackgroundScene::~BackgroundScene()
	{
	}

	void BackgroundScene::Start()
	{
		Scene::Start();
	}
	void BackgroundScene::Initialize()
	{
		// Main Camera Game Object
		{
			mMainCamera = object::Instantiate<GameObject>(eLayerType::Camera);
			mMainCamera->SetName(L"BackgroundSceneCamera");
			mMainCamera->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, 1.f));
			Camera* cameraComp = mMainCamera->AddComponent<Camera>();
			cameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
			//cameraComp->RegisterCameraInRenderer();
			cameraComp->DisableLayerMasks();
			cameraComp->TurnLayerMask(eLayerType::Background, true);
			//mMainCamera->AddComponent<CameraScript>();
			//mainCamera = cameraComp;
		}

		//Background
		{
			mBackground = object::Instantiate<GameObject>(eLayerType::Background);
			mBackground->SetName(L"Background");
			Transform* tr = mBackground->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.f, 0.f, 999.f));
			tr->SetScale(Vector3(128.0f, 72.0f, 1.f));

			SpriteRenderer* sr = mBackground->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> material = std::make_shared<Material>();
			std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"DefaultBackgroundTexture");
			std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"RectShader");

			material->SetRenderingMode(eRenderingMode::Transparent);
			material->SetTexture(eTextureSlot::T0, texture);
			material->SetShader(shader);

			Resources::Insert<Material>(L"DefaultBackgroundMaterial", material);

			sr->SetMaterial(material);
			sr->SetMesh(mesh);

			object::DontDestroyOnLoad(mBackground);
		}


		/*{
#pragma region Get Window Size
			RECT winRect;
			GetClientRect(application.GetHwnd(), &winRect);

			float width = static_cast<float>(winRect.right - winRect.left);
			float height = static_cast<float>(winRect.bottom - winRect.top);
			Vector3 originLT = Vector3(0.f - width / 2.f, height / 2.f, 0.f);
#pragma endregion

#pragma region Background
			std::shared_ptr<Material> material = Resources::Find<Material>(L"MTRL_ColorRect");
			Vector3 scale = Vector3::One;
			scale = Vector3(width, height, 1.f);
			int colorRed = 121;
			int colorGreen = 186;
			int colorBlue = 255;
			int colorAlpha = 255;

			material->SetData(eGPUParam::Int, &colorRed);
			material->SetData(eGPUParam::Int, &colorGreen);
			material->SetData(eGPUParam::Int, &colorBlue);
			material->SetData(eGPUParam::Int, &colorAlpha);

			Vector3 pos = Vector3::Zero;
			pos.z = 5.f;

			Vector3 rot = Vector3::One;
			LayerObject* layerObj = object::Instantiate<LayerObject>(eLayerType::BackGround, pos, rot, scale);
			layerObj->GetComponent<SpriteRenderer>()->SetMaterial(material);
			layerObj->SetName(L"Title_BackGround");
			layerObj->SetMove(false);

#pragma endregion
		}*/
	}
	void BackgroundScene::Update()
	{
		Scene::Update();
	}
	void BackgroundScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}
	void BackgroundScene::Render()
	{
		Scene::Render();
	}

	void BackgroundScene::OnEnter()
	{
		Scene::OnEnter();
	}
	void BackgroundScene::OnExit()
	{
		Scene::OnExit();
	}

	void BackgroundScene::LoadResources()
	{
	}

	void BackgroundScene::LoadBackground()
	{
	}
}