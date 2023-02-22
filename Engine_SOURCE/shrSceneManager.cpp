#include "shrSceneManager.h"
#include "shrTransform.h"
#include "shrRenderer.h"
#include "shrTexture.h"
#include "shrResources.h"
#include "shrMeshRenderer.h"
#include "shrSpriteRenderer.h"
#include "shrCamera.h"
#include "shrPlayerScript.h"
#include "shrCameraScript.h"
#include "shrGridScript.h"

namespace shr
{
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Initialize()
	{
		mActiveScene = new Scene();
		mActiveScene->Initialize();

		//Grid Object
		{
			GameObject* gridObj = new GameObject();
			Transform* gridTr = new Transform();
			gridObj->AddComponent(gridTr);
			MeshRenderer* gridMr = new MeshRenderer();
			gridObj->AddComponent(gridMr);
			gridObj->AddComponent(new GridScript());

			gridMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			gridMr->SetMaterial(Resources::Find<Material>(L"GridMaterial"));

			mActiveScene->AddGameObject(gridObj, eLayerType::Grid);
		}

		// Main Camera Game Object
		{
			GameObject* cameraObj = new GameObject();
			Transform* cameraTr = new Transform();
			cameraTr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
			cameraObj->AddComponent(cameraTr);
			Camera* cameraComp = new Camera();
			cameraComp->RegisterCameraInRenderer();
			cameraObj->AddComponent(cameraComp);
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			CameraScript* cameraScript = new CameraScript();
			cameraObj->AddComponent(cameraScript);

			mActiveScene->AddGameObject(cameraObj, eLayerType::Camera);
		}

		//UI CameraObj
		{
			GameObject* cameraUIObj = new GameObject();
			Transform* cameraUITr = new Transform();
			cameraUITr->SetPosition(Vector3(0.f, 0.f, 0.f));
			cameraUIObj->AddComponent(cameraUITr);
			Camera* cameraUIComp = new Camera();
			cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
			cameraUIObj->AddComponent(cameraUIComp);
			mActiveScene->AddGameObject(cameraUIObj, eLayerType::Camera);
			cameraUIComp->DisableLayerMasks();
			cameraUIComp->TurnLayerMask(eLayerType::UI, true);
		}

		// Light Object
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		{
			GameObject* spriteObj = new GameObject();
			spriteObj->SetName(L"LIGHT");
			Transform* spriteTr = new Transform();
			spriteTr->SetPosition(Vector3(0.0f, 0.0f, 11.0f));
			spriteTr->SetScale(Vector3(5.0f, 5.0f, 1.0f));
			spriteObj->AddComponent(spriteTr);

			SpriteRenderer* sr = new SpriteRenderer();
			spriteObj->AddComponent(sr);

		//	std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> spriteMaterial = Resources::Find<Material>(L"SpriteMaterial");

			//Vector2 vec2(1.0f, 1.0f);
			//spriteMaterial->SetData(eGPUParam::Vector2, &vec2);

			sr->SetMaterial(spriteMaterial);
			sr->SetMesh(mesh);

			mActiveScene->AddGameObject(spriteObj, eLayerType::Player);
		}

		//SMILE RECT
		{
			GameObject* obj = new GameObject();
			obj->SetName(L"SMILE");
			Transform* tr = new Transform();
			tr->SetPosition(Vector3(0.0f, 0.0f, 11.0f));
			tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2));
			tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
			obj->AddComponent(tr);

			MeshRenderer* mr = new MeshRenderer();
			obj->AddComponent(mr);

			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"RectMaterial");

			Vector2 vec2(1.0f, 1.0f);
			mateiral->SetData(eGPUParam::Vector2, &vec2);

			mr->SetMaterial(mateiral);
			mr->SetMesh(mesh);

			PlayerScript* playerScript = new PlayerScript();
			obj->AddComponent(playerScript);

			mActiveScene->AddGameObject(obj, eLayerType::Player);
		
		//SMILE RECT CHILD
			GameObject* child = new GameObject();
			child->SetName(L"SMILE");
			Transform* childTr = new Transform();
			childTr->SetPosition(Vector3(2.0f, 0.0f, 0.0f));
			childTr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
			child->AddComponent(childTr);
			childTr->SetParent(tr);

			MeshRenderer* childMr = new MeshRenderer();
			child->AddComponent(childMr);


			std::shared_ptr<Material> childmateiral = Resources::Find<Material>(L"RectMaterial");

			childMr->SetMaterial(childmateiral);
			childMr->SetMesh(mesh);

			mActiveScene->AddGameObject(child, eLayerType::Player);
		}

		//HPBAR
		{
			GameObject* hpBar = new GameObject();
			Transform* hpBarTr = new Transform();
			hpBarTr->SetPosition(Vector3(-5.f, 3.f, 10.f));
			hpBarTr->SetScale(Vector3(1.f, 1.f, 1.f));
			hpBar->AddComponent(hpBarTr);

			SpriteRenderer* hpBarSR = new SpriteRenderer();
			hpBar->AddComponent(hpBarSR);

			std::shared_ptr<Mesh> hpMesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> hpMaterial = Resources::Find<Material>(L"UIMaterial");
			//std::shared_ptr<Texture> hpTexture = Resources::Find<Texture>(L"UIMaterial");
			//hpMaterial->SetTexture(hpTexture);

			hpBarSR->SetMesh(hpMesh);
			hpBarSR->SetMaterial(hpMaterial);

			mActiveScene->AddGameObject(hpBar, eLayerType::UI);
		}

		mActiveScene->Initialize();
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
	}

	void SceneManager::FixedUpdate()
	{
		mActiveScene->FixedUpdate();
	}

	void SceneManager::Render()
	{
		mActiveScene->Render();
	}

	void SceneManager::Release()
	{
		delete mActiveScene;
		mActiveScene = nullptr;
	}
}