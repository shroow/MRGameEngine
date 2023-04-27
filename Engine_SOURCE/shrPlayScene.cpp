#include "shrPlayScene.h"
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
#include "shrCollisionManager.h"
#include "shrPlayer.h"
#include "shrMonster.h"
#include "shrPlayerScript.h"
#include "shrUnitScript.h"
#include "shrCollider2D.h"

namespace shr
{
	PlayScene::PlayScene()
		: Scene(eSceneType::Play)
		, mMainCamera(nullptr)
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		return;

		LoadResources();

		// Main Camera Game Object
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera);
		mMainCamera = cameraObj->AddComponent<Camera>();
		mMainCamera->SetProjectionType(Camera::eProjectionType::Orthographic);
		//cameraComp->RegisterCameraInRenderer();
		mMainCamera->TurnLayerMask(eLayerType::UI, false);
		cameraObj->AddComponent<CameraScript>();

		//UI Camera
		GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
		cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		cameraUIComp->DisableLayerMasks();
		cameraUIComp->TurnLayerMask(eLayerType::SystemUI, true);

		//Directional Light
		{
			GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player);
			directionalLight->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -100.0f));
			Light* lightComp = directionalLight->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
			object::DontDestroyOnLoad(directionalLight);
		}

		//Mouse
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Mouse);
			//obj->AddComponent<MouseScript>();
			object::DontDestroyOnLoad(obj);
		}


		//Field(Player)
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Background);
			obj->SetName(L"PlayerField");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(-4.5f, 1.5f, 10.f));
			Collider2D* collider = obj->AddComponent<Collider2D>();
			collider->SetName(L"PlayerFieldCollider");
			collider->SetType(eColliderType::Rect);
			collider->SetSize(Vector2(8.5f, 10.5f));
		}
		//Field(Monster)
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Background);
			obj->SetName(L"MonsterField");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(6.5f, 1.5f, 10.f));
			Collider2D* collider = obj->AddComponent<Collider2D>();
			collider->SetName(L"MonsterFieldCollider");
			collider->SetType(eColliderType::Rect);
			collider->SetSize(Vector2(8.5f, 10.5f));
		}

		//Knight1
		{
			Player* obj = object::Instantiate<Player>(eLayerType::Monster);
			obj->SetName(L"FreeKnightv1c1");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(-3.0f, 3.5f, 5.0f));
			//tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2));
			//tr->SetScale(Vector3(1.5f, 1.0f, 1.0f));
			tr->SetScale(Vector3(1.5f, 1.5f, 1.0f));
			Collider2D* collider = obj->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			//collider->SetCenter(Vector2(0.2f, 0.2f));
			//collider->SetSize(Vector2(1.5f, 1.5f));

			//HPBar
			{
				// HPBAR
				GameObject* hpBar = object::Instantiate<GameObject>(eLayerType::Monster);
				hpBar->SetName(L"HPBAR");
				Transform* hpBarTR = hpBar->GetComponent<Transform>();
				hpBarTR->SetParent(tr);
				hpBarTR->SetPosition(Vector3(0.0f, -0.65f, 0.0f));
				hpBarTR->SetScale(Vector3(1.0f, 0.2f, 1.0f));

				SpriteRenderer* hpsr = hpBar->AddComponent<SpriteRenderer>();
				hpBar->AddComponent(hpsr);
				std::shared_ptr<Mesh> hpmesh = Resources::Find<Mesh>(L"RectMesh");
				std::shared_ptr<Material> hpspriteMaterial = std::make_shared<Material>();
				std::shared_ptr<Texture> hpTex = Resources::Find<Texture>(L"RedBarTexture");
				std::shared_ptr<Shader> hpShader = Resources::Find<Shader>(L"UIShader");
				hpspriteMaterial->SetTexture(eTextureSlot::T0, hpTex);
				hpspriteMaterial->SetShader(hpShader);
				hpsr->SetMesh(hpmesh);
				hpsr->SetMaterial(hpspriteMaterial);

				// MPBAR
				GameObject* mpBar = object::Instantiate<GameObject>(eLayerType::Monster);
				mpBar->SetName(L"MPBAR");
				Transform* mpBarTR = mpBar->GetComponent<Transform>();
				mpBarTR->SetParent(tr);
				mpBarTR->SetPosition(Vector3(0.0f, -0.8f, 0.0f));
				mpBarTR->SetScale(Vector3(1.0f, 0.2f, 1.0f));

				SpriteRenderer* mpSR = mpBar->AddComponent<SpriteRenderer>();
				mpBar->AddComponent(mpSR);
				std::shared_ptr<Mesh> mpMesh = Resources::Find<Mesh>(L"RectMesh");
				std::shared_ptr<Material> mpSpriteMaterial = std::make_shared<Material>();;
				std::shared_ptr<Texture> mpTex = Resources::Find<Texture>(L"BlueBarTexture");
				std::shared_ptr<Shader> mpShader = Resources::Find<Shader>(L"UIShader");
				mpSpriteMaterial->SetTexture(eTextureSlot::T0, mpTex);
				mpSpriteMaterial->SetShader(mpShader);
				mpSR->SetMesh(mpMesh);
				mpSR->SetMaterial(mpSpriteMaterial);
			}

			SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"SpriteMaterial");
			mr->SetMaterial(mateiral);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			//Script
			UnitScript* script = obj->AddComponent<UnitScript>();
			script->SetChar(L"FreeKnightv1c1");

			//Animation add(using script)
			{
				script->LoadCharAnim(eCharState::Idle, Vector2::Zero
					, Vector2(0.f, 33.f), Vector2(120.f, 47.f)
					, 10, 0.1f, eAtlasType::Column);
				script->LoadCharAnim(eCharState::Attack, Vector2::Zero
					, Vector2(0.f, 33.f), Vector2(120.f, 47.f)
					, 10, 0.1f, eAtlasType::Column);
				script->LoadCharAnim(eCharState::Skill, Vector2::Zero
					, Vector2(0.f, 33.f), Vector2(120.f, 47.f)
					, 12, 0.1f, eAtlasType::Column);
				script->LoadCharAnim(eCharState::Death, Vector2::Zero
					, Vector2(0.f, 33.f), Vector2(120.f, 47.f)
					, 10, 0.1f, eAtlasType::Column);
				script->LoadCharAnim(eCharState::Run, Vector2::Zero
					, Vector2(0.f, 33.f), Vector2(120.f, 47.f)
					, 10, 0.1f, eAtlasType::Column);
				script->LoadCharAnim(eCharState::Hit, Vector2::Zero
					, Vector2(0.f, 33.f), Vector2(120.f, 47.f)
					, 1, 0.1f, eAtlasType::Column);
			}

			script->PlayCharAnim(eCharState::Idle);
		}

		//Monster
		{
			GameObject* obj = object::Instantiate<Player>(eLayerType::Monster);
			obj->SetName(L"BallandChainBot");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(6.0f, 3.5f, 5.0f));
			//tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2));
			//tr->SetScale(Vector3(3.5f, 1.0f, 1.0f));
			tr->SetScale(Vector3(1.5f, 1.5f, 1.0f));
			Collider2D* collider = obj->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			//collider->SetCenter(Vector2(0.2f, 0.2f));
			//collider->SetSize(Vector2(1.5f, 1.5f));

			// HPBAR
			{
				// HPBAR
				GameObject* hpBar = object::Instantiate<GameObject>(eLayerType::Monster);
				hpBar->SetName(L"HPBAR");
				Transform* hpBarTR = hpBar->GetComponent<Transform>();
				hpBarTR->SetParent(tr);
				hpBarTR->SetPosition(Vector3(0.0f, -0.65f, 0.0f));
				hpBarTR->SetScale(Vector3(1.0f, 0.2f, 1.0f));

				SpriteRenderer* hpsr = hpBar->AddComponent<SpriteRenderer>();
				hpBar->AddComponent(hpsr);
				std::shared_ptr<Mesh> hpmesh = Resources::Find<Mesh>(L"RectMesh");
				std::shared_ptr<Material> hpspriteMaterial = std::make_shared<Material>();
				std::shared_ptr<Texture> hpTex = Resources::Find<Texture>(L"RedBarTexture");
				std::shared_ptr<Shader> hpShader = Resources::Find<Shader>(L"UIShader");
				hpspriteMaterial->SetTexture(eTextureSlot::T0, hpTex);
				hpspriteMaterial->SetShader(hpShader);
				hpsr->SetMesh(hpmesh);
				hpsr->SetMaterial(hpspriteMaterial);

				// MPBAR
				GameObject* mpBar = object::Instantiate<GameObject>(eLayerType::Monster);
				mpBar->SetName(L"MPBAR");
				Transform* mpBarTR = mpBar->GetComponent<Transform>();
				mpBarTR->SetParent(tr);
				mpBarTR->SetPosition(Vector3(0.0f, -0.8f, 0.0f));
				mpBarTR->SetScale(Vector3(1.0f, 0.2f, 1.0f));

				SpriteRenderer* mpSR = mpBar->AddComponent<SpriteRenderer>();
				mpBar->AddComponent(mpSR);
				std::shared_ptr<Mesh> mpMesh = Resources::Find<Mesh>(L"RectMesh");
				std::shared_ptr<Material> mpSpriteMaterial = std::make_shared<Material>();;
				std::shared_ptr<Texture> mpTex = Resources::Find<Texture>(L"BlueBarTexture");
				std::shared_ptr<Shader> mpShader = Resources::Find<Shader>(L"UIShader");
				mpSpriteMaterial->SetTexture(eTextureSlot::T0, mpTex);
				mpSpriteMaterial->SetShader(mpShader);
				mpSR->SetMesh(mpMesh);
				mpSR->SetMaterial(mpSpriteMaterial);
			}

			SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"SpriteMaterial");
			mr->SetMaterial(mateiral);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			//Script
			UnitScript* script = obj->AddComponent<UnitScript>();
			script->SetChar(L"BallandChainBot");

			//Animation add(using script)
			{
				script->LoadCharAnim(eCharState::Idle, Vector2::Zero
					, Vector2(0.f, 0.f), Vector2(126.f, 39.f)
					, 5, 0.1f, eAtlasType::Row);
				script->LoadCharAnim(eCharState::Attack, Vector2(-0.1f, 0.f)
					, Vector2(0.f, 0.f), Vector2(126.f, 39.f)
					, 8, 0.1f, eAtlasType::Row);
				script->LoadCharAnim(eCharState::Skill, Vector2::Zero
					, Vector2(0.f, 0.f), Vector2(126.f, 39.f)
					, 4, 0.1f, eAtlasType::Row);
				script->LoadCharAnim(eCharState::Death, Vector2::Zero
					, Vector2(0.f, 0.f), Vector2(126.f, 39.f)
					, 5, 0.1f, eAtlasType::Row);
				script->LoadCharAnim(eCharState::Run, Vector2::Zero
					, Vector2(0.f, 0.f), Vector2(126.f, 39.f)
					, 8, 0.1f, eAtlasType::Row);
				script->LoadCharAnim(eCharState::Hit, Vector2::Zero
					, Vector2(0.f, 0.f), Vector2(126.f, 39.f)
					, 2, 0.1f, eAtlasType::Row);
			}

			script->PlayCharAnim(eCharState::Idle);

			script->SetIsStore(true);
		}

		{
			// Coin
			GameObject* hpBar = object::Instantiate<GameObject>(eLayerType::SystemUI);
			hpBar->SetName(L"CoinUI");
			Transform* hpBarTR = hpBar->GetComponent<Transform>();
			hpBarTR->SetPosition(Vector3(-10.2f, -3.9f, 12.0f));
			hpBarTR->SetScale(Vector3(2.5f, 1.5f, 1.0f));

			SpriteRenderer* hpsr = hpBar->AddComponent<SpriteRenderer>();
			hpBar->AddComponent(hpsr);
			std::shared_ptr<Mesh> hpmesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> hpspriteMaterial = std::make_shared<Material>();
			hpspriteMaterial->SetTexture(eTextureSlot::T0, Resources::Find<Texture>(L"MoneyPanelTexture"));
			hpspriteMaterial->SetShader(Resources::Find<Shader>(L"UIShader"));
			hpsr->SetMesh(hpmesh);
			hpsr->SetMaterial(hpspriteMaterial);
		}

		//TempNum
		{
			GameObject* hpBar = object::Instantiate<GameObject>(eLayerType::SystemUI);
			hpBar->SetName(L"CoinNum");
			Transform* hpBarTR = hpBar->GetComponent<Transform>();
			hpBarTR->SetPosition(Vector3(-9.7f, -4.0f, 12.0f));
			hpBarTR->SetScale(Vector3(0.8f, 0.8f, 1.0f));

			SpriteRenderer* hpsr = hpBar->AddComponent<SpriteRenderer>();
			hpBar->AddComponent(hpsr);
			std::shared_ptr<Mesh> hpmesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> hpspriteMaterial = std::make_shared<Material>();
			hpspriteMaterial->SetTexture(eTextureSlot::T0, Resources::Find<Texture>(L"TempNumTexture"));
			hpspriteMaterial->SetShader(Resources::Find<Shader>(L"UIShader"));
			hpsr->SetMesh(hpmesh);
			hpsr->SetMaterial(hpspriteMaterial);
		}

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Player, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Monster, eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Background, eLayerType::Monster, true);
		CollisionManager::MouseCollisionLayerCheck(eLayerType::Player);
		CollisionManager::MouseCollisionLayerCheck(eLayerType::Monster);

		Scene::Initialize();
	}
	void PlayScene::Update()
	{	
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Test);
		}
	}
	void PlayScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}
	void PlayScene::Render()
	{
		Scene::Render();
	}
	void PlayScene::OnEnter()
	{
		Scene::OnEnter();
	}
	void PlayScene::OnExit()
	{
		Scene::OnExit();
	}
	void PlayScene::LoadResources()
	{
	}
	void PlayScene::CreateMonster(int num, Vector3 pos)
	{
	}
}