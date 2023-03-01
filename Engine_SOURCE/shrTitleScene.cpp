#include "shrTitleScene.h"
#include "shrResources.h"

#include "shrObject.h"
#include "shrGameObject.h"

#include "shrTransform.h"

#include "shrMeshRenderer.h"
#include "shrSpriteRenderer.h"
#include "shrMultiShaderRenderer.h"

#include "shrPlayerScript.h"
#include "shrCameraScript.h"
#include "shrGridScript.h"
#include "shrFadeInScript.h"
#include "shrBikerScript.h"

namespace shr
{
	TitleScene::TitleScene()
		: Scene()
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		Scene::Initialize();

		LoadResources();

		// Main Camera Game Object
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		cameraComp->RegisterCameraInRenderer();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraObj->AddComponent<CameraScript>();
		

		//UI CameraObj
		GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
		cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		cameraUIComp->DisableLayerMasks();
		cameraUIComp->TurnLayerMask(eLayerType::UI, true);


		//Grid Object
		{
			GameObject* gridObject = object::Instantiate<GameObject>(eLayerType::None);
			MeshRenderer* gridMr = gridObject->AddComponent<MeshRenderer>();
			gridMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			gridMr->SetMaterial(Resources::Find<Material>(L"GridMaterial"));
			GridScript* gridScript = gridObject->AddComponent<GridScript>();
			gridScript->SetCamera(cameraComp);
		}

		// Light Object
		{
			GameObject* spriteObj = object::Instantiate<GameObject>(eLayerType::Player);
			spriteObj->SetName(L"LIGHT");
			Transform* spriteTr = spriteObj->GetComponent<Transform>();
			spriteTr->SetPosition(Vector3(5.0f, 5.0f, 11.0f));
			spriteTr->SetScale(Vector3(5.0f, 5.0f, 1.0f));

			SpriteRenderer* sr = spriteObj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> spriteMaterial = Resources::Find<Material>(L"SpriteMaterial");
			sr->SetMaterial(spriteMaterial);
			sr->SetMesh(mesh);
		}

		//SMILE RECT /SMILE RECT CHild
		{
			//SMILE RECT
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Player);
			obj->SetName(L"SMILE");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(-3.0f, 0.0f, 11.0f));
			tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2));
			tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));

			MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"RectMaterial");
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMaterial(mateiral);
			mr->SetMesh(mesh);
			obj->AddComponent<PlayerScript>();

			//SMILE RECT CHild
			GameObject* child = object::Instantiate<GameObject>(eLayerType::Player);
			child->SetName(L"SMILE");
			Transform* childTr = child->GetComponent<Transform>();
			childTr->SetPosition(Vector3(2.0f, 0.0f, 0.0f));
			childTr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
			childTr->SetParent(tr);

			MeshRenderer* childMr = child->AddComponent<MeshRenderer>();
			std::shared_ptr<Material> childmateiral = Resources::Find<Material>(L"RectMaterial");
			childMr->SetMaterial(childmateiral);
			childMr->SetMesh(mesh);
		}

		//HPBAR
		{
			GameObject* hpBar = object::Instantiate<GameObject>(eLayerType::UI);
			hpBar->SetName(L"HPBAR");
			Transform* hpBarTR = hpBar->GetComponent<Transform>();
			hpBarTR->SetPosition(Vector3(-5.0f, 3.0f, 12.0f));
			hpBarTR->SetScale(Vector3(1.0f, 1.0f, 1.0f));

			SpriteRenderer* hpsr = hpBar->AddComponent<SpriteRenderer>();
			hpBar->AddComponent(hpsr);
			std::shared_ptr<Mesh> hpmesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> hpspriteMaterial = Resources::Find<Material>(L"UIMaterial");
			hpsr->SetMesh(hpmesh);
			hpsr->SetMaterial(hpspriteMaterial);
		}

		{//Fadein Obj
			GameObject* fadeinObject = object::Instantiate<GameObject>(eLayerType::CameraEffect);
			fadeinObject->SetName(L"FadeIn");
			Transform* fadeinTR = fadeinObject->GetComponent<Transform>();
			fadeinTR->SetPosition(Vector3(3.0f, 3.0f, 3.0f));
			fadeinTR->SetScale(Vector3(3.0f, 3.0f, 3.0f));

			SpriteRenderer* fadeinSR = fadeinObject->AddComponent<SpriteRenderer>();

			std::shared_ptr<Mesh> fadeinMesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> fadeinMaterial = Resources::Find<Material>(L"FadeInMaterial");
			fadeinSR->SetMesh(fadeinMesh);
			fadeinSR->SetMaterial(fadeinMaterial);
			fadeinObject->AddComponent<FadeInScript>();
		}


		//Biker1
		{
			GameObject* bikerObj = object::Instantiate<GameObject>(eLayerType::Player);
			bikerObj->SetName(L"LIGHT");
			Transform* bikerTr = bikerObj->GetComponent<Transform>();
			bikerTr->SetPosition(Vector3(-3.0f, 2.0f, 10.0f));
			bikerTr->SetScale(Vector3(4.0f, 1.0f, 1.0f));

			SpriteRenderer* sr = bikerObj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> spriteMaterial = Resources::Find<Material>(L"Biker_Idle_Material");
			sr->SetMaterial(spriteMaterial);
			sr->SetMesh(mesh);


			//bikerObj->AddComponent<BikerScript>();
		}

		//Biker2
		{
			GameObject* bikerObj = object::Instantiate<GameObject>(eLayerType::Monster);
			bikerObj->SetName(L"Biker2");

			Transform* bikerTr = bikerObj->GetComponent<Transform>();
			bikerTr->SetPosition(Vector3(-3.0f, -2.0f, 10.0f));
			bikerTr->SetScale(Vector3(1.0f, 1.0f, 1.0f));

			SpriteRenderer* SR = bikerObj->AddComponent<SpriteRenderer>();

			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			SR->SetMesh(mesh);

			std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"Biker_Death");
			std::shared_ptr<Shader> fadeinShader = Resources::Find<Shader>(L"FadeInShader");

			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->SetShader(fadeinShader);
			material->SetTexture(texture);

			Resources::Insert<Material>(L"Biker_Death2", material);
			SR->SetMaterial(material); 

			//bikerObj->AddComponent<BikerScript>();
		}

		////Total Object Test Result : 500 < x < 600
		//{
		//	for (int i = 0; i < 500; i++)
		//	{
		//		int count = i * 5;
		//		GameObject* bikerObj = object::Instantiate<GameObject>(eLayerType::Player);
		//		bikerObj->SetName(L"LIGHT");
		//		Transform* bikerTr = bikerObj->GetComponent<Transform>();
		//		bikerTr->SetPosition(Vector3(-3.0f + (float)count, 2.0f, 10.0f));
		//		bikerTr->SetScale(Vector3(4.0f, 1.0f, 1.0f));

		//		SpriteRenderer* sr = bikerObj->AddComponent<SpriteRenderer>();
		//		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		//		std::shared_ptr<Material> spriteMaterial = Resources::Find<Material>(L"Biker_Idle_Material");
		//		sr->SetMaterial(spriteMaterial);
		//		sr->SetMesh(mesh);
		//	}
		//}

	}
	void TitleScene::Update()
	{
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
		Scene::OnEnter();
	}
	void TitleScene::OnExit()
	{
		Scene::OnExit();
	}
	void TitleScene::LoadResources()
	{
		Scene::LoadResources();

		//Biker_Idle
		{
			std::shared_ptr<Material> material = std::make_shared<Material>();
			std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"SpriteShader");
			std::shared_ptr<Texture> texture 
				= Resources::Load<Texture>(L"Biker_Idle", L"Biker\\Idle.png");

			material->SetShader(shader);
			material->SetTexture(texture);

			Resources::Insert<Material>(L"Biker_Idle_Material", material);
		}

		//Biker_Death
		{
			std::shared_ptr<Material> material = std::make_shared<Material>();
			std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"FadeInShader");
			
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"Biker_Death", L"Biker\\Death.png");

			material->SetShader(shader);
			material->SetTexture(texture);

			Resources::Insert<Material>(L"Biker_Death_Material", material);
		}
	}
}