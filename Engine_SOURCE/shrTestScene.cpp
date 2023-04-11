#include "shrTestScene.h"
#include "shrSceneManager.h"
#include "shrTransform.h"
#include "shrInput.h"
#include "shrCamera.h"
#include "shrPlayer.h"
#include "shrPlayerScript.h"
#include "shrGameObject.h"
#include "shrObject.h"
#include "shrSpriteRenderer.h"
#include "shrMonsterScript.h"
#include "shrCameraScript.h"
#include "shrAnimator.h"
#include "shrCollisionManager.h"
#include "shrParticleSystem.h"
#include "shrPaintShader.h"

#include "shrUnitComponent.h"
#include "shrMouseScript.h"

namespace shr
{
	TestScene::TestScene()
		: Scene(eSceneType::Test)
		, mMainCamera(nullptr)
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

		//Mouse
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Mouse);
			//obj->AddComponent<MouseScript>();
			object::DontDestroyOnLoad(obj);
		}

		// Main Camera Game Object
		mMainCamera = object::Instantiate<GameObject>(eLayerType::Camera);
		mMainCamera->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, 0.f));
		Camera* cameraComp = mMainCamera->AddComponent<Camera>();
		cameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		//cameraComp->RegisterCameraInRenderer();
		cameraComp->TurnLayerMask(eLayerType::SystemUI, false);
		mMainCamera->AddComponent<CameraScript>();
		mainCamera = GetMainCamera();
		
		////UI Camera
		//GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera);
		//Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
		//cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		//cameraUIComp->DisableLayerMasks();
		//cameraUIComp->TurnLayerMask(eLayerType::SystemUI, true);

		//Directional Light
		{
			GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player);
			directionalLight->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -100.0f));
			Light* lightComp = directionalLight->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
			object::DontDestroyOnLoad(directionalLight);
		}

		////Particle
		//{
		//	GameObject* obj = object::Instantiate<Player>(eLayerType::Particle);
		//	obj->SetName(L"PARTICLE");
		//	Transform* tr = obj->GetComponent<Transform>();
		//	tr->SetPosition(Vector3(0.0f, 0.0f, 100.0f));
		//	obj->AddComponent<ParticleSystem>();
		//}

		//paint shader
		{
			std::shared_ptr<PaintShader> paintShader = Resources::Find<PaintShader>(L"PaintShader");
			//L"SmileTexture"
			std::shared_ptr<Texture> paintTex = Resources::Find<Texture>(L"PaintTexture");
			paintShader->SetTarget(paintTex);
			paintShader->OnExcute();
		}
		 
		//SMILE RECT
		{
			Player* obj = object::Instantiate<Player>(eLayerType::Player);
			obj->SetName(L"SMILE");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(-2.0f, 2.0f, 5.0f));
			tr->SetScale(Vector3(2.0f, 2.0f, 1.0f));
			//tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2 / 2.0f));
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

		//Line
		{
			GameObject* line = object::Instantiate<Player>(eLayerType::Monster);
			line->SetName(L"CenterLine");
			Transform* tr = line->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.0f, 0.0f, 5.0f));
			//tr->SetRotation(Vector3(0.0f, 0.0f, 30.f));
			tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
			Collider2D* collider = line->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Line);
			//그리드(10.f) 한칸당 반지름 20.f
			collider->SetRadius(90.f);
		}

		//Field(Player)
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Background);
			obj->SetName(L"PlayerField");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(-25.f, 0.f, 100.f));
			Collider2D* collider = obj->AddComponent<Collider2D>();
			collider->SetName(L"PlayerFieldCollider");
			collider->SetType(eColliderType::Rect);
			collider->SetSize(Vector2(40.0f, 40.0f));
		}

		//Field(Monster)
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Background);
			obj->SetName(L"MonsterField");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(25.f, 0.f, 100.f));
			Collider2D* collider = obj->AddComponent<Collider2D>();
			collider->SetName(L"MonsterFieldCollider");
			collider->SetType(eColliderType::Rect);
			collider->SetSize(Vector2(40.0f, 40.0f));
		}

		//Knight1
		{
			Player* obj = object::Instantiate<Player>(eLayerType::Monster);
			obj->SetName(L"FreeKnightv1c1");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(-20.0f, -0.5f, 5.0f));
			tr->SetScale(Vector3(6.0f, 6.0f, 1.0f));
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
				hpBarTR->SetPosition(Vector3(0.0f, -0.60f, 0.0f));
				hpBarTR->SetScale(Vector3(0.75f, 0.14f, 1.0f));

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
				mpBarTR->SetPosition(Vector3(0.0f, -0.75f, 0.0f));
				mpBarTR->SetScale(Vector3(0.75f, 0.14f, 1.0f));

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
			MonsterScript* script = obj->AddComponent<MonsterScript>();
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
			tr->SetPosition(Vector3(20.0f, 5.5f, 5.0f));
			tr->SetScale(Vector3(6.0f, 6.0f, 1.0f));
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
				hpBarTR->SetPosition(Vector3(0.0f, -0.60f, 0.0f));
				hpBarTR->SetScale(Vector3(0.75f, 0.14f, 1.0f));

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
				mpBarTR->SetPosition(Vector3(0.0f, -0.75f, 0.0f));
				mpBarTR->SetScale(Vector3(0.75f, 0.14f, 1.0f));

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
			MonsterScript* script = obj->AddComponent<MonsterScript>();
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
			hpBar->SetName(L"CoinUI");
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

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Background);
		CollisionManager::CollisionLayerCheck(eLayerType::Monster, eLayerType::Monster);
		CollisionManager::CollisionLayerCheck(eLayerType::Monster, eLayerType::Background);
		CollisionManager::MouseCollisionLayerCheck(eLayerType::Player);
		CollisionManager::MouseCollisionLayerCheck(eLayerType::Monster);

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

		//Test1 Texture
		{
			//Biker
			Resources::Load<Texture>(L"Biker_Idle", L"Monsters\\Cyberpunk\\Biker\\Biker_idle.png");
			Resources::Load<Texture>(L"Biker_Death", L"Monsters\\Cyberpunk\\Biker\\Biker_death.png");
			Resources::Load<Texture>(L"Biker_Attack", L"Monsters\\Cyberpunk\\Biker\\Biker_attack1.png");
			Resources::Load<Texture>(L"Biker_Run", L"Monsters\\Cyberpunk\\Biker\\Biker_run.png");


			//Monster
			Resources::Load<Texture>(L"Monster_Idle", L"Monster\\Idle.png");
			Resources::Load<Texture>(L"Monster_Death", L"Monster\\Death.png");
			Resources::Load<Texture>(L"Monster_Attack2", L"Monster\\Attack2.png");
		}

		//NightBorne /Column
		Resources::Load<Texture>(L"NightBorne_Atlas", L"Monsters\\NightBorne\\NightBorne.png");
		
		Resources::Load<Texture>(L"CoinTexture", L"UI\\Coin.png");
		Resources::Load<Texture>(L"MoneyPanelTexture", L"UI\\MoneyPanel.png");
		Resources::Load<Texture>(L"BuyUITexture", L"UI\\BuyUI.png");
		Resources::Load<Texture>(L"SellUITexture", L"UI\\SellUI.png");
		Resources::Load<Texture>(L"TempNumTexture", L"UI\\tempNum.png");

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
			//Resources::Load<Texture>(L"FreeKnightv1c1_Attack", L"FreeKnight_v1\\Colour1\\_Attack.png");
			/// 720x80/6							
			//Resources::Load<Texture>(L"FreeKnightv1c1_Attack2", L"FreeKnight_v1\\Colour1\\_Attack2.png");
			/// 720x80/6							
			//Resources::Load<Texture>(L"FreeKnightv1c1_Attack2NoMovement", L"FreeKnight_v1\\Colour1\\_Attack2NoMovement.png");
			/// 1200x80/10							
			//Resources::Load<Texture>(L"FreeKnightv1c1_AttackCombo", L"FreeKnight_v1\\Colour1\\_AttackCombo.png");
			/// 1200x80/10							
			Resources::Load<Texture>(L"FreeKnightv1c1_Attack", L"FreeKnight_v1\\Colour1\\_AttackComboNoMovement.png");
			/// 480x80_4						
			//Resources::Load<Texture>(L"FreeKnightv1c1_AttackNoMovement", L"FreeKnight_v1\\Colour1\\_AttackNoMovement.png");
			/// 1200x80_10							
			Resources::Load<Texture>(L"FreeKnightv1c1_Death", L"FreeKnight_v1\\Colour1\\_Death.png");
			/// 1200x80_10							
			//Resources::Load<Texture>(L"FreeKnightv1c1_DeathNoMovement", L"FreeKnight_v1\\Colour1\\_DeathNoMovement.png");
			/// 120x80_1							
			Resources::Load<Texture>(L"FreeKnightv1c1_Hit", L"FreeKnight_v1\\Colour1\\_Hit.png");
			/// 1200x80_10							
			Resources::Load<Texture>(L"FreeKnightv1c1_Idle", L"FreeKnight_v1\\Colour1\\_Idle.png");
			/// 1440x80_12							
			Resources::Load<Texture>(L"FreeKnightv1c1_Skill", L"FreeKnight_v1\\Colour1\\_Roll.png");
			/// 1200x80_10							
			Resources::Load<Texture>(L"FreeKnightv1c1_Run", L"FreeKnight_v1\\Colour1\\_Run.png");

			/////Colour2
			/// 480x80/5
			//Resources::Load<Texture>(L"FreeKnightv1c2_Attack", L"FreeKnight_v1\\Colour2\\_Attack.png");
			/// 720x80/6							  
			//Resources::Load<Texture>(L"FreeKnightv1c2_Attack2", L"FreeKnight_v1\\Colour2\\_Attack2.png");
			/// 720x80/6							  
			//Resources::Load<Texture>(L"FreeKnightv1c2_Attack2NoMovement", L"FreeKnight_v1\\Colour2\\_Attack2NoMovement.png");
			/// 1200x80/10							
			Resources::Load<Texture>(L"FreeKnightv1c2_Attack", L"FreeKnight_v1\\Colour2\\_AttackCombo.png");
			/// 1200x80/10							
			//Resources::Load<Texture>(L"FreeKnightv1c2_AttackComboNoMovement", L"FreeKnight_v1\\Colour2\\_AttackComboNoMovement.png");
			/// 480x80_4							  
			//Resources::Load<Texture>(L"FreeKnightv1c2_AttackNoMovement", L"FreeKnight_v1\\Colour2\\_AttackNoMovement.png");
			/// 1200x80_10							
			Resources::Load<Texture>(L"FreeKnightv1c2_Death", L"FreeKnight_v1\\Colour2\\_Death.png");
			/// 1200x80_10							
			//Resources::Load<Texture>(L"FreeKnightv1c2_DeathNoMovement", L"FreeKnight_v1\\Colour2\\_DeathNoMovement.png");
			/// 120x80_1							
			Resources::Load<Texture>(L"FreeKnightv1c2_Hit", L"FreeKnight_v1\\Colour2\\_Hit.png");
			/// 1200x80_10							
			Resources::Load<Texture>(L"FreeKnightv1c2_Idle", L"FreeKnight_v1\\Colour2\\_Idle.png");
			/// 1440x80_12							
			Resources::Load<Texture>(L"FreeKnightv1c2_Skill", L"FreeKnight_v1\\Colour2\\_Roll.png");
			/// 1200x80_10							
			Resources::Load<Texture>(L"FreeKnightv1c2_Run", L"FreeKnight_v1\\Colour2\\_Run.png");
		}
	}

	void TestScene::CreateMonster(int num , Vector3 pos)
	{
	}
}