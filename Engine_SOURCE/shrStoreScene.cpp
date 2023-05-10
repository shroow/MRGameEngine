#include "shrStoreScene.h"
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
#include "shrMouseScript.h"
#include "shrPlayerObject.h"
#include "shrPlayerScript.h"
#include "shrUnitObject.h"
#include "shrUnitScript.h"

#include "shrSceneInfo.h"
#include "shrNumUI.h"

namespace shr
{
	StoreScene::StoreScene()
		: Scene(eSceneType::Battle)
		, mStore(nullptr)
	{
	}

	StoreScene::~StoreScene()
	{
		if (mStore != nullptr)
			mStore->ClearDeck();
	}

	void StoreScene::Start()
	{
		{
			//Directional Light
			{
				GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player);
				directionalLight->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -100.0f));
				Light* lightComp = directionalLight->AddComponent<Light>();
				lightComp->SetType(eLightType::Directional);
				lightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 1.0f));

				directionalLight->DontDestroy(true);
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

				obj->DontDestroy(true);
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

				obj->DontDestroy(true);
			}

			//TempNum
			{
				NumUI* obj = object::Instantiate<NumUI>(eLayerType::SystemUI);
				obj->SetName(L"GoldNum");

				Transform* objTR = obj->GetComponent<Transform>();
				objTR->SetPosition(Vector3(-49.2f, -25.7f, 4.0f));
				objTR->SetScale(Vector3(1.5f, 1.5f, 1.0f));

				obj->DontDestroy(true);


				SceneManager::SetGoldUI(obj);
			}
			//CoinBack
			{
				GameObject* obj = object::Instantiate<GameObject>(eLayerType::SystemUI);
				obj->SetName(L"CoinUI");
				Transform* objTR = obj->GetComponent<Transform>();
				objTR->SetPosition(Vector3(-50.2f, -23.9f, 5.0f));
				objTR->SetScale(Vector3(8.5f, 5.5f, 1.0f));

				SpriteRenderer* objsr = obj->AddComponent<SpriteRenderer>();
				obj->AddComponent(objsr);
				std::shared_ptr<Mesh> objmesh = Resources::Find<Mesh>(L"RectMesh");
				std::shared_ptr<Material> objMaterial = std::make_shared<Material>();
				objMaterial->SetTexture(eTextureSlot::T0, Resources::Find<Texture>(L"MoneyPanelTexture"));
				objMaterial->SetShader(Resources::Find<Shader>(L"UIShader"));
				objsr->SetMesh(objmesh);
				objsr->SetMaterial(objMaterial);

				obj->DontDestroy(true);
			}
		}

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

	void StoreScene::Initialize()
	{
		//SceneInfo::LoadResourcesInfo();
		//LoadResources();

		// Main Camera Game Object
		mMainCamera = object::Instantiate<GameObject>(eLayerType::Camera);
		mMainCamera->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, 0.f));
		Camera* cameraComp = mMainCamera->AddComponent<Camera>();
		cameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		//cameraComp->RegisterCameraInRenderer();
		cameraComp->TurnLayerMask(eLayerType::SystemUI, true);
		//mMainCamera->AddComponent<CameraScript>();
		//mainCamera = cameraComp;
		
		
		//Store
		{
			mStore = object::Instantiate<PlayerObject>(eLayerType::Player);
			mStore->SetName(L"Store");

			Transform* tr = mStore->GetComponent<Transform>();
			tr->SetPosition(Vector3(1.f, 1.f, 4.0f));
			tr->SetRotation(Vector3(0.f, 0.f, 0.f));
			tr->SetScale(Vector3(6.0f, 6.0f, 1.0f));

			mStore->SetPlayerState(ePlayerType::Store);

			PlayerScript* playerScript = mStore->GetPlayerScirpt();
		}

		UnitObject* obj = object::Instantiate<UnitObject>(eLayerType::Monster);
		obj->SetCharType(eUnitType::FreeKnight);
		Transform* tr = obj->GetComponent<Transform>();
		tr->SetPosition(Vector3(-10.f, 0.f, 5.f));
		tr->SetRotation(Vector3(0.f, 0.f, 0.f));
		tr->SetScale(Vector3(6.0f, 6.0f, 1.0f));

		//Animation add(using script)
		UnitScript* monScript = obj->GetScript<UnitScript>();
		{
			monScript->LoadUnitAnim(eUnitType::FreeKnight);
		}
		monScript->PlayUnitAnim(eUnitState::Idle);

		monScript->SetIsStore(true);

		mStore->AddUnit(obj);

		//Timer
		{
			//타이머가 다떨어지면 상호작용을 해야되서 멤버로 들고 있어야됨
			//타이머숫자만큼 텍스처 렌더
		}

		RerollStore();
	}

	void StoreScene::Update()
	{
		PlayerObject* player = SceneManager::GetPlayer(); 
		NumUI* goldUI = SceneManager::GetGoldUI(); 

		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Battle);
		}

		if (Input::GetKeyDown(eKeyCode::R))
		{
			if (player->SubGold(1))
				RerollStore();
		}

		if (Input::GetKeyDown(eKeyCode::N_4))
		{
			player->AddGold(1);
		}
		if (Input::GetKeyDown(eKeyCode::N_5))
		{
			player->AddGold(5);
		}

		if (Input::GetKeyDown(eKeyCode::F))
		{
			if(player)

			if(player->SubGold(4))
				player->AddExp(4);
		}

		UINT gold = player->GetGold();
		goldUI->SetNum(gold);

		Scene::Update();
	}

	void StoreScene::FixedUpdate()
	{
		PlayerObject* player = SceneManager::GetPlayer();
		MouseObject* mouse = SceneManager::GetMouse();

		if (mouse->IsSelected())
		{
			UnitObject* selected = mouse->GetSelectedUnit();

			PlayerObject* owner = selected->GetOwner();

			if (selected->IsTrade())
			{
				if (owner->GetPlayerType() == ePlayerType::Store)
				{
					player->BuyUnit(selected);
				}
				else if (owner->GetPlayerType() == ePlayerType::Player)
				{
					player->SellUnit(selected);
				}
			}
		}

		Scene::FixedUpdate();
	}

	void StoreScene::Render()
	{
		Scene::Render();
	}

	void StoreScene::OnEnter()
	{
		Scene::OnEnter();
	}

	void StoreScene::OnExit()
	{
		Scene::OnExit();

		mStore->ClearDeck();

		Layer& layer = GetLayer(eLayerType::Monster);

		layer.OnExit();
	}

	void StoreScene::LoadResources()
	{
	}

	void StoreScene::RerollStore()
	{
		PlayerObject* player = SceneManager::GetPlayer();
		int level = player->GetStoreLevel();

		mStore->ClearDeck();

		//int storeNum = 0; //지정 레벨따라 숫자 변경할까?
		std::srand(time(NULL));

		for (int i = 0; i < level; ++i)
		{
			Vector3 pos(12.5f, 10.0f, 10.f);

			if (i < 3) {
				pos.x += i * 12.5f;
			}
			else if (i < 6) {
				pos.x += (i - 3) * 12.5f;
				pos.y -= 10.f;	
			}
			else if (i < 10) {
				pos.x += (i - 6) * 12.5f;
				pos.y -= 20.f;
			}
			else
				break;

			//Random eUnitType

			UINT random = rand() % ((UINT)eUnitType::End);
			/////////////////////////////

			CreateMonster((eUnitType)random, pos);
		}
	}

	void StoreScene::CreateMonster(eUnitType type, Vector3 pos)
	{
		UnitObject* obj = object::Instantiate<UnitObject>(eLayerType::Monster);
		obj->SetCharType(type);
		Transform* tr = obj->GetComponent<Transform>();
		tr->SetPosition(Vector3(pos));
		tr->SetRotation(Vector3(0.f, 0.f, 0.f));
		tr->SetScale(Vector3(6.0f, 6.0f, 1.0f));

		//Animation add(using script)
		UnitScript* monScript = obj->GetScript<UnitScript>();
		{
			monScript->LoadUnitAnim(type);
		}
		monScript->PlayUnitAnim(eUnitState::Idle);

		monScript->SetIsStore(true);

		mStore->AddUnit(obj);
	}
}