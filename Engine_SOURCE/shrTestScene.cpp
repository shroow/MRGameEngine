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

		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		//cameraComp->RegisterCameraInRenderer();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraObj->AddComponent<CameraScript>();

		////Back CameraObj
		//GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		//Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
		////cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		//cameraUIComp->DisableLayerMasks();
		//cameraUIComp->TurnLayerMask(eLayerType::Background, true);

		//Biker1
		{
			Player* obj = object::Instantiate<Player>(eLayerType::Player, this);
			obj->SetName(L"Biker1");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(-4.0f, 0.0f, 10.0f));
			//tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2));
			tr->SetScale(Vector3(5.0f, 1.0f, 1.0f));
			Collider2D* collider = obj->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			//collider->SetCenter(Vector2(0.2f, 0.2f));
			//collider->SetSize(Vector2(1.5f, 1.5f));
			//collider->SetScale(Vector2(1.5f, 1.5f));

			SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"Biker_Idle_Material");
			mr->SetMaterial(mateiral);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			obj->AddComponent<BikerScript>();

			//object::DontDestroyOnLoad(obj);
		}

		//Monster
		{
			GameObject* obj = object::Instantiate<Player>(eLayerType::Monster, this);
			obj->SetName(L"Monster");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(5.0f, 0.0f, 10.0f));
			//tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2 / 2.0f));
			tr->SetScale(Vector3(5.0f, 1.0f, 1.0f));
			Collider2D* collider = obj->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			//collider->SetCenter(Vector2(0.2f, 0.2f));
			//collider->SetSize(Vector2(1.5f, 1.5f));

			SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"Monster_Idle_Material");
			mr->SetMaterial(mateiral);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			obj->AddComponent<MonsterScript>();

			//object::DontDestroyOnLoad(obj);
		}

		////Background
		//{
		//	GameObject* back = object::Instantiate<GameObject>(eLayerType::Background);
		//	back->SetName(L"Background");
		//	Transform* backTR = back->GetComponent<Transform>();
		//	backTR->SetPosition(Vector3(1.0f, 1.0f, 100.0f));
		//	backTR->SetScale(Vector3(300.0f, 150.0f, 1.0f));

		//	SpriteRenderer* backsr = back->AddComponent<SpriteRenderer>();
		//	back->AddComponent(backsr);
		//	std::shared_ptr<Mesh> backmesh = Resources::Find<Mesh>(L"RectMesh");
		//	std::shared_ptr<Material> spriteMaterial = Resources::Find<Material>(L"UIMaterial");

		//	std::shared_ptr<Texture> texture
		//		= Resources::Load<Texture>(L"Background", L"PRE_ORIG_SIZE.png");
		//	spriteMaterial->SetTexture(texture);

		//	backsr->SetMesh(backmesh);
		//	backsr->SetMaterial(spriteMaterial);
		//}


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
}