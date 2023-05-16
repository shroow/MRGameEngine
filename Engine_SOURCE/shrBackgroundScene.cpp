#include "shrBackgroundScene.h"
#include "shrObject.h"
#include "shrTexture.h"
#include "shrResources.h"
#include "shrCamera.h"
#include "shrSpriteRenderer.h"

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
			mMainCamera->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, 1.f));
			Camera* cameraComp = mMainCamera->AddComponent<Camera>();
			cameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
			//cameraComp->RegisterCameraInRenderer();
			cameraComp->TurnLayerMask(eLayerType::SystemUI, false);
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			//mMainCamera->AddComponent<CameraScript>();
			//mainCamera = cameraComp;
		}

		//Directional Light
		{
			GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player);
			directionalLight->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -100.0f));
			Light* lightComp = directionalLight->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 1.0f));

			directionalLight->DontDestroy(true);
		}

		//Background
		{
			mBackground = object::Instantiate<GameObject>(eLayerType::Background);
			Transform* tr = mBackground->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.f, 0.f, 999.f));
			tr->SetScale(Vector3(12.f, 7.f, 1.f));

			SpriteRenderer* sr = mBackground->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> material = std::make_shared<Material>();
			std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"DefaultBackground");
			std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"SpriteShader");

			material->SetTexture(eTextureSlot::T4, texture);
			material->SetShader(shader);

			Resources::Insert<Material>(L"DefaultBackground", material);

			sr->SetMesh(mesh);
			sr->SetMaterial(material);
		}

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