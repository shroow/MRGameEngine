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
#include "shrMonsterScript.h"
#include "shrParticleSystem.h"

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
		//paint shader
		std::shared_ptr<PaintShader> paintShader = Resources::Find<PaintShader>(L"PaintShader");
		//L"SmileTexture"
		std::shared_ptr<Texture> paintTex = Resources::Find<Texture>(L"PaintTexture");
		paintShader->SetTarget(paintTex);
		paintShader->OnExcute();

		//{
		//	GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player);
		//	directionalLight->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -100.0f));
		//	Light* lightComp = directionalLight->AddComponent<Light>();
		//	lightComp->SetType(eLightType::Directional);
		//	lightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		//}

		{
			GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player);
			directionalLight->GetComponent<Transform>()->SetPosition(Vector3(3.0f, 0.0f, 0.0f));
			Light* lightComp = directionalLight->AddComponent<Light>();
			lightComp->SetType(eLightType::Point);
			lightComp->SetRadius(10.0f);
			lightComp->SetDiffuse(Vector4(1.0f, 0.0f, 0.0f, 1.0f));
		}

		//Particle
		{
			Player* obj = object::Instantiate<Player>(eLayerType::Particle);
			obj->SetName(L"PARTICLE");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.0f, 0.0f, 100.0f));
			obj->AddComponent<ParticleSystem>();
		}

		//GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		//Camera* cameraComp = cameraObj->AddComponent<Camera>();
		////cameraComp->RegisterCameraInRenderer();
		//cameraComp->TurnLayerMask(eLayerType::UI, false);
		//cameraObj->AddComponent<CameraScript>();

		//// Main Camera Game Object
		//GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera);
		//Camera* cameraComp = cameraObj->AddComponent<Camera>();
		//cameraComp->SetProjectionType(Camera::eProjectionType::Perspective);
		////cameraComp->RegisterCameraInRenderer();
		//cameraComp->TurnLayerMask(eLayerType::UI, false);
		//cameraObj->AddComponent<CameraScript>();
		//mainCamera = cameraComp;

		// UI Camera
		//GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera);
		//Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
		//cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		//cameraUIComp->DisableLayerMasks();
		//cameraUIComp->TurnLayerMask(eLayerType::UI, true);

		//// Grid Object
		//GameObject* gridObject = object::Instantiate<GameObject>(eLayerType::None);
		//MeshRenderer* gridMr = gridObject->AddComponent<MeshRenderer>();
		//gridMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//gridMr->SetMaterial(Resources::Find<Material>(L"GridMaterial"));
		//GridScript* gridScript = gridObject->AddComponent<GridScript>();
		//gridScript->SetCamera(cameraComp);

		//SMILE RECT
		{
			Player* obj = object::Instantiate<Player>(eLayerType::Player);
			obj->SetName(L"Zelda");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(2.0f, 2.0f, 2.0f));
			//tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2));
			//tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
			Collider2D* collider = obj->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			//collider->SetCenter(Vector2(0.2f, 0.2f));
			//collider->SetSize(Vector2(1.5f, 1.5f));
			Animator* animator = obj->AddComponent<Animator>();
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Zelda", L"Zelda.png");
			animator->Create(L"Idle", texture, Vector2(0.0f, 0.0f), Vector2(120.0f, 130.0f), Vector2::Zero, 3, 0.1f);
			animator->Create(L"MoveDown", texture, Vector2(0.0f, 520.0f), Vector2(120.0f, 130.0f), Vector2::Zero, 8, 0.1f);

			animator->Play(L"Idle", true);

			SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"SpriteMaterial");
			mr->SetMaterial(mateiral);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
			obj->AddComponent<PlayerScript>();
			obj->AddComponent<MonsterScript>();
			object::DontDestroyOnLoad(obj);
		}

		//SMILE RECT
		{
			Player* obj = object::Instantiate<Player>(eLayerType::Player);
			obj->SetName(L"SMILE");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(-2.0f, 2.0f, 5.0f));
			//tr->SetScale(Vector3(2.0f, 1.0f, 1.0f));
			//tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2 / 2.0f));
			//tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
			Collider2D* collider = obj->AddComponent<Collider2D>();
			collider->SetSize(Vector2(2.0f, 2.0f));
			collider->SetType(eColliderType::Rect);
			//collider->SetCenter(Vector2(0.2f, 0.2f));
			//collider->SetSize(Vector2(1.5f, 1.5f));

			SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"RectMaterial");
			mr->SetMaterial(mateiral);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
			object::DontDestroyOnLoad(obj);
		}

		////SMILE RECT CHild
		//GameObject* child = object::Instantiate<GameObject>(eLayerType::Player);
		//child->SetName(L"SMILE");
		//Transform* childTr = child->GetComponent<Transform>();
		//childTr->SetPosition(Vector3(2.0f, 0.0f, 11.0f));
		//childTr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
		//childTr->SetParent(tr);

		//MeshRenderer* childMr = child->AddComponent<MeshRenderer>();
		//std::shared_ptr<Material> childmateiral = Resources::Find<Material>(L"RectMaterial");
		//childMr->SetMaterial(childmateiral);
		//childMr->SetMesh(mesh);

		//// HPBAR
		//GameObject* hpBar = object::Instantiate<GameObject>(eLayerType::Player);
		//hpBar->SetName(L"HPBAR");
		//Transform* hpBarTR = hpBar->GetComponent<Transform>();
		//hpBarTR->SetPosition(Vector3(-5.0f, 3.0f, 12.0f));
		//hpBarTR->SetScale(Vector3(1.0f, 1.0f, 1.0f));

		//SpriteRenderer* hpsr = hpBar->AddComponent<SpriteRenderer>();
		//hpBar->AddComponent(hpsr);
		//std::shared_ptr<Mesh> hpmesh = Resources::Find<Mesh>(L"RectMesh");
		//std::shared_ptr<Material> hpspriteMaterial = Resources::Find<Material>(L"UIMaterial");
		//hpsr->SetMesh(hpmesh);
		//hpsr->SetMaterial(hpspriteMaterial);

		//CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Player, true);

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
	}
	void TitleScene::OnExit()
	{
	}
}
