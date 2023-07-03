#include "shrSettingScene.h"
#include "shrObject.h"
#include "shrTexture.h"
#include "shrResources.h"
#include "shrCamera.h"
#include "shrSpriteRenderer.h"

namespace shr
{
	SettingScene::SettingScene()
		: Scene(eSceneType::Setting)
		, mBackground(nullptr)
		, mSoundUI(nullptr)
		, mDeviceUI(nullptr)
	{
	}
	SettingScene::~SettingScene()
	{
	}

	void SettingScene::Start()
	{
		Scene::Start();
	}
	void SettingScene::Initialize()
	{
		// Main Camera Game Object
		mMainCamera = object::Instantiate<GameObject>(eLayerType::Camera);
		mMainCamera->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, 1.f));
		Camera* cameraComp = mMainCamera->AddComponent<Camera>();
		cameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		//cameraComp->RegisterCameraInRenderer();
		cameraComp->TurnLayerMask(eLayerType::SystemUI, true);
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		//mMainCamera->AddComponent<CameraScript>();
		//mainCamera = cameraComp;


		mBackground = object::Instantiate<GameObject>(eLayerType::SystemUI);
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

		{
			mSoundUI = object::Instantiate<GameObject>(eLayerType::SystemUI);

			mDeviceUI = object::Instantiate<GameObject>(eLayerType::SystemUI);
		}

	}
	void SettingScene::Update()
	{
		Scene::Update();
	}
	void SettingScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}
	void SettingScene::Render()
	{
		Scene::Render();
	}

	void SettingScene::OnEnter()
	{
		Scene::OnEnter();
	}
	void SettingScene::OnExit()
	{
		Scene::OnExit();
	}

	void SettingScene::LoadResources()
	{
	}

	void SettingScene::LoadBackground()
	{
	}
}