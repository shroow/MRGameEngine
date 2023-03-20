#include "shrTestScene.h"
#include "shrSceneManager.h"
#include "shrTransform.h"
#include "shrInput.h"
#include "shrCamera.h"
#include "shrPlayer.h"
#include "shrPlayerScript.h"
#include "shrBikerScript.h"
#include "shrGameObject.h"
#include "shrObject.h"
#include "shrSpriteRenderer.h"
#include "shrMonsterScript.h"
#include "shrCameraScript.h"
#include "shrAnimator.h"
#include "shrCollisionManager.h"

namespace shr
{
	TestScene::TestScene()
		: Scene(eSceneType::Test)
	{
	}
	TestScene::~TestScene()
	{
	}
	void TestScene::Initialize()
	{
		LoadResources();

		//GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		//Camera* cameraComp = cameraObj->AddComponent<Camera>();
		////cameraComp->RegisterCameraInRenderer();
		//cameraComp->TurnLayerMask(eLayerType::UI, false);
		//cameraObj->AddComponent<CameraScript>();

		// Main Camera Game Object
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		cameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		//cameraComp->RegisterCameraInRenderer();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraObj->AddComponent<CameraScript>();
		mainCamera = cameraComp;


		//UI Camera
		GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
		cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		cameraUIComp->DisableLayerMasks();
		cameraUIComp->TurnLayerMask(eLayerType::UI, true);


		//Biker1
		{
			Player* obj = object::Instantiate<Player>(eLayerType::Player);
			obj->SetName(L"FreeKnightv1c1");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(-2.0f, 0.0f, 5.0f));
			//tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2));
			//tr->SetScale(Vector3(1.5f, 1.0f, 1.0f));
			tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
			Collider2D* collider = obj->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			//collider->SetCenter(Vector2(0.2f, 0.2f));
			//collider->SetSize(Vector2(1.5f, 1.5f));
			Animator* animator = obj->AddComponent<Animator>();
			{
				animator->Create(L"FreeKnightv1c1_Attack"
					, Resources::Find<Texture>(L"FreeKnightv1c1_AttackComboNoMovement")
					, Vector2(0.f, 33.f), Vector2(120.f, 47.f)
					, Vector2(0.0f, 0.0f), 10, 0.1f, eAtlasType::Column);
				animator->Create(L"FreeKnightv1c1_Death"
					, Resources::Find<Texture>(L"FreeKnightv1c1_DeathNoMovement")
					, Vector2(0.f, 33.f), Vector2(120.f, 47.f)
					, Vector2(0.0f, 0.0f), 10, 0.1f, eAtlasType::Column);
				animator->Create(L"FreeKnightv1c1_Hit"
					, Resources::Find<Texture>(L"FreeKnightv1c1_Hit")
					, Vector2(0.f, 33.f), Vector2(120.f, 47.f)
					, Vector2(0.0f, 0.0f), 1, 0.1f, eAtlasType::Column);
				animator->Create(L"FreeKnightv1c1_Idle"
					, Resources::Find<Texture>(L"FreeKnightv1c1_Idle")
					, Vector2(0.f, 33.f), Vector2(120.f, 47.f)
					, Vector2(0.0f, 0.0f), 10, 0.1f, eAtlasType::Column);
				animator->Create(L"FreeKnightv1c1_Roll"
					, Resources::Find<Texture>(L"FreeKnightv1c1_Roll")
					, Vector2(0.f, 33.f), Vector2(120.f, 47.f)
					, Vector2(0.0f, 0.0f), 12, 0.1f, eAtlasType::Column);
				animator->Create(L"FreeKnightv1c1_Run"
					, Resources::Find<Texture>(L"FreeKnightv1c1_Run")
					, Vector2(0.f, 33.f), Vector2(120.f, 47.f)
					, Vector2(0.0f, 0.0f), 10, 0.1f, eAtlasType::Column);

				animator->Play(L"FreeKnightv1c1_Idle", true);
			}

			{
				// HPBAR
				GameObject* hpBar = object::Instantiate<GameObject>(eLayerType::UI);
				hpBar->SetName(L"HPBAR");
				Transform* hpBarTR = hpBar->GetComponent<Transform>();
				hpBarTR->SetPosition(Vector3(0.0f, -1.0f, 12.0f));
				hpBarTR->SetScale(Vector3(1.0f, 1.0f, 1.0f));
				hpBarTR->SetParent(tr);

				SpriteRenderer* hpsr = hpBar->AddComponent<SpriteRenderer>();
				hpBar->AddComponent(hpsr);
				std::shared_ptr<Mesh> hpmesh = Resources::Find<Mesh>(L"RectMesh");
				std::shared_ptr<Material> hpspriteMaterial = Resources::Find<Material>(L"UIMaterial");
				hpsr->SetMesh(hpmesh);
				hpsr->SetMaterial(hpspriteMaterial);
			}

			SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"SpriteMaterial");
			mr->SetMaterial(mateiral);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
			obj->AddComponent<BikerScript>();
			object::DontDestroyOnLoad(obj);
		}

		//Monster
		{
			GameObject* obj = object::Instantiate<Player>(eLayerType::Monster);
			obj->SetName(L"BallandChainBot");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(2.0f, 0.0f, 5.0f));
			//tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2));
			//tr->SetScale(Vector3(3.5f, 1.0f, 1.0f));
			tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
			Collider2D* collider = obj->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			//collider->SetCenter(Vector2(0.2f, 0.2f));
			//collider->SetSize(Vector2(1.5f, 1.5f));
			Animator* animator = obj->AddComponent<Animator>();
			{
				animator->Create(L"BallandChainBot_Idle",
					Resources::Find<Texture>(L"BallandChainBot_Idle")
					, Vector2(0.f, 0.f), Vector2(126.f, 39.f)
					, Vector2::Zero, 5, 0.1f, eAtlasType::Row);
				animator->Create(L"BallandChainBot_Attack",
					Resources::Find<Texture>(L"BallandChainBot_Attack")
					, Vector2(0.f, 0.f), Vector2(126.f, 39.f)
					, Vector2(-0.1f, 0.f), 8, 0.1f, eAtlasType::Row);
				animator->Create(L"BallandChainBot_Charge",
					Resources::Find<Texture>(L"BallandChainBot_Charge")
					, Vector2(0.f, 0.f), Vector2(126.f, 39.f)
					, Vector2::Zero, 4, 0.1f, eAtlasType::Row);
				animator->Create(L"BallandChainBot_Death",
					Resources::Find<Texture>(L"BallandChainBot_Death")
					, Vector2(0.f, 0.f), Vector2(126.f, 39.f)
					, Vector2::Zero, 5, 0.1f, eAtlasType::Row);
				animator->Create(L"BallandChainBot_Hit",
					Resources::Find<Texture>(L"BallandChainBot_Hit")
					, Vector2(0.f, 0.f), Vector2(126.f, 39.f)
					, Vector2::Zero, 2, 0.1f, eAtlasType::Row);
				animator->Create(L"BallandChainBot_Run",
					Resources::Find<Texture>(L"BallandChainBot_Run")
					, Vector2(0.f, 0.f), Vector2(126.f, 39.f)
					, Vector2::Zero, 8, 0.1f, eAtlasType::Row);

				animator->Play(L"BallandChainBot_Idle", true);
			}

			{
				// HPBAR
				GameObject* hpBar = object::Instantiate<GameObject>(eLayerType::UI);
				hpBar->SetName(L"HPBAR");
				Transform* hpBarTR = hpBar->GetComponent<Transform>();
				hpBarTR->SetPosition(Vector3(0.0f, -1.0f, 12.0f));
				hpBarTR->SetScale(Vector3(1.0f, 1.0f, 1.0f));
				hpBarTR->SetParent(tr);

				SpriteRenderer* hpsr = hpBar->AddComponent<SpriteRenderer>();
				hpBar->AddComponent(hpsr);
				std::shared_ptr<Mesh> hpmesh = Resources::Find<Mesh>(L"RectMesh");
				std::shared_ptr<Material> hpspriteMaterial = Resources::Find<Material>(L"UIMaterial");
				hpsr->SetMesh(hpmesh);
				hpsr->SetMaterial(hpspriteMaterial);
			}

			SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"SpriteMaterial");
			mr->SetMaterial(mateiral);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
			obj->AddComponent<MonsterScript>();
			object::DontDestroyOnLoad(obj);
		}

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Player, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);


		Scene::Initialize();
	}
	void TestScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Title);
		}

		Scene::Update();
	}
	void TestScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}
	void TestScene::Render()
	{
		Scene::Render();
	}
	void TestScene::OnEnter()
	{
		Scene::OnEnter();
	}
	void TestScene::OnExit()
	{
		Scene::OnExit();
	}
	void TestScene::LoadResources()
	{
		Scene::LoadResources();

		//Test1 materials
		{
			//Biker_Idle
			{
				std::shared_ptr<Material> material = std::make_shared<Material>();
				std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");

				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"Biker_Idle", L"Biker\\Idle.png");

				material->SetShader(spriteShader);
				material->SetTexture(texture);
				material->SetRenderingMode(eRenderingMode::Transparent);

				Resources::Insert<Material>(L"Biker_Idle_Material", material);
			}

			//Biker_Death
			{
				std::shared_ptr<Material> material = std::make_shared<Material>();
				std::shared_ptr<Shader> fadeinShader = Resources::Find<Shader>(L"FadeInShader");

				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"Biker_Death", L"Biker\\Death.png");

				material->SetShader(fadeinShader);
				material->SetTexture(texture);
				material->SetRenderingMode(eRenderingMode::Transparent);

				Resources::Insert<Material>(L"Biker_Death_Material", material);
			}

			//Biker_Attack1
			{
				std::shared_ptr<Material> material = std::make_shared<Material>();
				std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");

				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"Biker_Attack1", L"Biker\\Attack1.png");

				material->SetShader(spriteShader);
				material->SetTexture(texture);
				material->SetRenderingMode(eRenderingMode::Transparent);

				Resources::Insert<Material>(L"Biker_Attack1_Material", material);
			}

			//Biker_Attack2
			{
				std::shared_ptr<Material> material = std::make_shared<Material>();
				std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");

				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"Biker_Attack2", L"Biker\\Attack2.png");

				material->SetShader(spriteShader);
				material->SetTexture(texture);
				material->SetRenderingMode(eRenderingMode::Transparent);

				Resources::Insert<Material>(L"Biker_Attack2_Material", material);
			}

			//Biker_Attack3
			{
				std::shared_ptr<Material> material = std::make_shared<Material>();
				std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");

				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"Biker_Attack3", L"Biker\\Attack3.png");

				material->SetShader(spriteShader);
				material->SetTexture(texture);
				material->SetRenderingMode(eRenderingMode::Transparent);

				Resources::Insert<Material>(L"Biker_Attack3_Material", material);
			}


			//Monster_Idle
			{
				std::shared_ptr<Material> material = std::make_shared<Material>();
				std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");

				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"Monster_Idle", L"Monster\\Idle.png");

				material->SetShader(spriteShader);
				material->SetTexture(texture);
				material->SetRenderingMode(eRenderingMode::Transparent);

				Resources::Insert<Material>(L"Monster_Idle_Material", material);
			}

			//Monster_Death
			{
				std::shared_ptr<Material> material = std::make_shared<Material>();
				std::shared_ptr<Shader> fadeinShader = Resources::Find<Shader>(L"FadeInShader");

				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"Monster_Death", L"Monster\\Death.png");

				material->SetShader(fadeinShader);
				material->SetTexture(texture);
				material->SetRenderingMode(eRenderingMode::Transparent);

				Resources::Insert<Material>(L"Monster_Death_Material", material);
			}

			//Monster_Attack1
			{
				std::shared_ptr<Material> material = std::make_shared<Material>();
				std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");

				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"Monster_Attack2", L"Monster\\Attack2.png");

				material->SetShader(spriteShader);
				material->SetTexture(texture);
				material->SetRenderingMode(eRenderingMode::Transparent);

				Resources::Insert<Material>(L"Monster_Attack2_Material", material);
			}
		}

		//Textures
		{
			//NightBorne /Column
			Resources::Load<Texture>(L"NightBorne_Atlas", L"Monsters\\NightBorne\\NightBorne.png");

			//Ball and Chain Bot /Row
			{
				/// 126x195/5
				Resources::Load<Texture>(L"BallandChainBot_Idle", L"Monsters\\Ball and Chain Bot\\idle.png");
				/// 126x312/8
				Resources::Load<Texture>(L"BallandChainBot_Attack", L"Monsters\\Ball and Chain Bot\\attack.png");
				/// 126x156/4
				Resources::Load<Texture>(L"BallandChainBot_Charge", L"Monsters\\Ball and Chain Bot\\charge.png");
				/// 126x195/5
				Resources::Load<Texture>(L"BallandChainBot_Death", L"Monsters\\Ball and Chain Bot\\death.png");
				/// 126x78/2
				Resources::Load<Texture>(L"BallandChainBot_Hit", L"Monsters\\Ball and Chain Bot\\hit.png");
				/// 126x312/8
				Resources::Load<Texture>(L"BallandChainBot_Run", L"Monsters\\Ball and Chain Bot\\run.png");
				/// 126x78/2
				Resources::Load<Texture>(L"BallandChainBot_TransitionCharge", L"Monsters\\Ball and Chain Bot\\transition to charge.png");
			}

			//FreeKight_v1  /Column
			{
				//////Colour1
				/// 480x80/5
				Resources::Load<Texture>(L"FreeKnightv1c1_Attack", L"FreeKnight_v1\\Colour1\\_Attack.png");
				/// 720x80/6							
				Resources::Load<Texture>(L"FreeKnightv1c1_Attack2", L"FreeKnight_v1\\Colour1\\_Attack2.png");
				/// 720x80/6							
				Resources::Load<Texture>(L"FreeKnightv1c1_Attack2NoMovement", L"FreeKnight_v1\\Colour1\\_Attack2NoMovement.png");
				/// 1200x80/10							
				Resources::Load<Texture>(L"FreeKnightv1c1_AttackCombo", L"FreeKnight_v1\\Colour1\\_AttackCombo.png");
				/// 1200x80/10							
				Resources::Load<Texture>(L"FreeKnightv1c1_AttackComboNoMovement", L"FreeKnight_v1\\Colour1\\_AttackComboNoMovement.png");
				/// 480x80_4						
				Resources::Load<Texture>(L"FreeKnightv1c1_AttackNoMovement", L"FreeKnight_v1\\Colour1\\_AttackNoMovement.png");
				/// 1200x80_10							
				Resources::Load<Texture>(L"FreeKnightv1c1_Death", L"FreeKnight_v1\\Colour1\\_Death.png");
				/// 1200x80_10							
				Resources::Load<Texture>(L"FreeKnightv1c1_DeathNoMovement", L"FreeKnight_v1\\Colour1\\_DeathNoMovement.png");
				/// 120x80_1							
				Resources::Load<Texture>(L"FreeKnightv1c1_Hit", L"FreeKnight_v1\\Colour1\\_Hit.png");
				/// 1200x80_10							
				Resources::Load<Texture>(L"FreeKnightv1c1_Idle", L"FreeKnight_v1\\Colour1\\_Idle.png");
				/// 1440x80_12							
				Resources::Load<Texture>(L"FreeKnightv1c1_Roll", L"FreeKnight_v1\\Colour1\\_Roll.png");
				/// 1200x80_10							
				Resources::Load<Texture>(L"FreeKnightv1c1_Run", L"FreeKnight_v1\\Colour1\\_Run.png");

				/////Colour2
				/// 480x80/5
				Resources::Load<Texture>(L"FreeKnightv1c2_Attack", L"FreeKnight_v1\\Colour2\\_Attack.png");
				/// 720x80/6
				Resources::Load<Texture>(L"FreeKnightv1c2_Attack2", L"FreeKnight_v1\\Colour2\\_Attack2.png");
				/// 720x80/6
				Resources::Load<Texture>(L"FreeKnightv1c2_Attack2NoMovement", L"FreeKnight_v1\\Colour2\\_Attack2NoMovement.png");
				/// 1200x80/10
				Resources::Load<Texture>(L"FreeKnightv1c2_Attack", L"FreeKnight_v1\\Colour2\\_AttackCombo.png");
				/// 1200x80/10
				Resources::Load<Texture>(L"FreeKnightv1c2_AttackComboNoMovement", L"FreeKnight_v1\\Colour2\\_AttackComboNoMovement.png");
				/// 480x80_4
				Resources::Load<Texture>(L"FreeKnightv1c2_AttackNoMovement", L"FreeKnight_v1\\Colour2\\_AttackNoMovement.png");
				/// 1200x80_10
				Resources::Load<Texture>(L"FreeKnightv1c2_Death", L"FreeKnight_v1\\Colour2\\_Death.png");
				/// 1200x80_10
				Resources::Load<Texture>(L"FreeKnightv1c2_DeathNoMovement", L"FreeKnight_v1\\Colour2\\_DeathNoMovement.png");
				/// 120x80_1
				Resources::Load<Texture>(L"FreeKnightv1c2_Hit", L"FreeKnight_v1\\Colour2\\_Hit.png");
				/// 1200x80_10
				Resources::Load<Texture>(L"FreeKnightv1c2_Idle", L"FreeKnight_v1\\Colour2\\_Idle.png");
				/// 1440x80_12
				Resources::Load<Texture>(L"FreeKnightv1c2_Roll", L"FreeKnight_v1\\Colour2\\_Roll.png");
				/// 1200x80_10
				Resources::Load<Texture>(L"FreeKnightv1c2_Run", L"FreeKnight_v1\\Colour2\\_Run.png");
			}
		}

		////Animations
		//{
		//	Animator* animator = new Animator();				
		//	
		//	animator->Create(L"Default"
		//		, Resources::Find<Texture>(L"Default")
		//		, Vector2(0.f, 0.f), Vector2(126.f, 312.f)
		//		, Vector2::Zero, 8, 0.f);

		//	//FreeKnight_v1
		//	{
		//		animator->Create(L"FreeKnightv1c1_Attack"
		//			, Resources::Find<Texture>(L"FreeKnightv1c1_Attack")
		//			, Vector2(0.f, 0.f), Vector2(480.f, 80.f)
		//			, Vector2::Zero, 5, 0.f);
		//		animator->Create(L"FreeKnightv1c1_Attack2"
		//			, Resources::Find<Texture>(L"FreeKnightv1c1_Attack2")
		//			, Vector2(0.f, 0.f), Vector2(720.f, 80.f)
		//			, Vector2::Zero, 6, 0.f);
		//		animator->Create(L"FreeKnightv1c1_Attack2NoMovement"
		//			, Resources::Find<Texture>(L"FreeKnightv1c1_Attack2NoMovement")
		//			, Vector2(0.f, 0.f), Vector2(720.f, 80.f)
		//			, Vector2::Zero, 6, 0.f);
		//		animator->Create(L"FreeKnightv1c1_AttackCombo"
		//			, Resources::Find<Texture>(L"FreeKnightv1c1_AttackCombo")
		//			, Vector2(0.f, 0.f), Vector2(1200.f, 80.f)
		//			, Vector2::Zero, 10, 0.f);
		//		animator->Create(L"FreeKnightv1c1_AttackComboNoMovement"
		//			, Resources::Find<Texture>(L"FreeKnightv1c1_AttackComboNoMovement")
		//			, Vector2(0.f, 0.f), Vector2(1200.f, 80.f)
		//			, Vector2::Zero, 10, 0.f);
		//		animator->Create(L"FreeKnightv1c1_AttackNoMovement"
		//			, Resources::Find<Texture>(L"FreeKnightv1c1_AttackNoMovement")
		//			, Vector2(0.f, 0.f), Vector2(480.f, 80.f)
		//			, Vector2::Zero, 4, 0.f);
		//		animator->Create(L"FreeKnightv1c1_Death"
		//			, Resources::Find<Texture>(L"FreeKnightv1c1_Death")
		//			, Vector2(0.f, 0.f), Vector2(1200.f, 80.f)
		//			, Vector2::Zero, 10, 0.f);
		//		animator->Create(L"FreeKnightv1c1_DeathNoMovement"
		//			, Resources::Find<Texture>(L"FreeKnightv1c1_DeathNoMovement")
		//			, Vector2(0.f, 0.f), Vector2(1200.f, 80.f)
		//			, Vector2::Zero, 10, 0.f);
		//		animator->Create(L"FreeKnightv1c1_Hit"
		//			, Resources::Find<Texture>(L"FreeKnightv1c1_Hit")
		//			, Vector2(0.f, 0.f), Vector2(120.f, 80.f)
		//			, Vector2::Zero, 1, 0.f);
		//		animator->Create(L"FreeKnightv1c1_Idle"
		//			, Resources::Find<Texture>(L"FreeKnightv1c1_Idle")
		//			, Vector2(0.f, 0.f), Vector2(1200.f, 80.f)
		//			, Vector2::Zero, 10, 0.f);
		//		animator->Create(L"FreeKnightv1c1_Roll"
		//			, Resources::Find<Texture>(L"FreeKnightv1c1_Roll")
		//			, Vector2(0.f, 0.f), Vector2(1440.f, 80.f)
		//			, Vector2::Zero, 12, 0.f);
		//		animator->Create(L"FreeKnightv1c1_Run"
		//			, Resources::Find<Texture>(L"FreeKnightv1c1_Run")
		//			, Vector2(0.f, 0.f), Vector2(1200.f, 80.f)
		//			, Vector2::Zero, 10, 0.f);
		//	}

		//	//BotandChainBot //Row
		//	{
		//		animator->Create(L"BallandChainBot_Idle", 
		//			Resources::Find<Texture>(L"BallandChainBot_Idle")
		//			, Vector2(0.f, 0.f), Vector2(126.f, 195.f)
		//			, Vector2::Zero, 5, 0.f, eAtlasType::Row);
		//		animator->Create(L"BallandChainBot_Attack",
		//			Resources::Find<Texture>(L"BallandChainBot_Attack")
		//			, Vector2(0.f, 0.f), Vector2(126.f, 312.f)
		//			, Vector2::Zero, 8, 0.f, eAtlasType::Row);
		//		animator->Create(L"BallandChainBot_Charge",
		//			Resources::Find<Texture>(L"BallandChainBot_Charge")
		//			, Vector2(0.f, 0.f), Vector2(126.f, 156.f)
		//			, Vector2::Zero, 4, 0.f, eAtlasType::Row);
		//		animator->Create(L"BallandChainBot_Death",
		//			Resources::Find<Texture>(L"BallandChainBot_Death")
		//			, Vector2(0.f, 0.f), Vector2(126.f, 195.f)
		//			, Vector2::Zero, 5, 0.f, eAtlasType::Row);
		//		animator->Create(L"BallandChainBot_Hit",
		//			Resources::Find<Texture>(L"BallandChainBot_Hit")
		//			, Vector2(0.f, 0.f), Vector2(126.f, 78.f)
		//			, Vector2::Zero, 2, 0.f, eAtlasType::Row);
		//		animator->Create(L"BallandChainBot_Run",
		//			Resources::Find<Texture>(L"BallandChainBot_Run")
		//			, Vector2(0.f, 0.f), Vector2(126.f, 312.f)
		//			, Vector2::Zero, 8, 0.f, eAtlasType::Row);
		//		animator->Create(L"BallandChainBot_TransitionCharge",
		//			Resources::Find<Texture>(L"BallandChainBot_TransitionCharge")
		//			, Vector2(0.f, 0.f), Vector2(126.f, 78.f)
		//			, Vector2::Zero, 2, 0.f, eAtlasType::Row);
		//	}
		//}
	}
}