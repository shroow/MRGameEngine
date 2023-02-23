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
#include "shrObject.h"

namespace shr
{
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Initialize()
	{
		mActiveScene = new Scene();
		mActiveScene->Initialize();

		//Grid Object
		{
			GameObject* gridObject = object::Instantiate<GameObject>(eLayerType::None);
			MeshRenderer* gridMr = gridObject->AddComponent<MeshRenderer>();
			gridMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			gridMr->SetMaterial(Resources::Find<Material>(L"GridMaterial"));
			gridObject->AddComponent<GridScript>();
		}

		// Main Camera Game Object
		{
			GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera
				, Vector3(0.f, 0.f, 0.f), Vector3(0.f, 0.f, 0.f));
			Camera* cameraComp = cameraObj->AddComponent<Camera>();

			cameraComp->RegisterCameraInRenderer();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			
			cameraObj->AddComponent<CameraScript>();
		}

		//UI CameraObj
		{
			GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera
				, Vector3(0.f, 0.f, 0.f), Vector3(0.f, 0.f, 0.f));
			Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();

			cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
			cameraUIComp->DisableLayerMasks();
			cameraUIComp->TurnLayerMask(eLayerType::UI, true);
		}

		// Light Object
		{
			GameObject* spriteObj = object::Instantiate<GameObject>(eLayerType::Player
				, Vector3(0.0f, 0.0f, 11.0f), Vector3(5.0f, 5.0f, 1.0f));
			spriteObj->SetName(L"LIGHT");

			SpriteRenderer* sr = spriteObj->AddComponent<SpriteRenderer>();

			sr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			sr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));
		}

		//SMILE RECT
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Camera, Vector3(0.f, 0.f, 11.0f), Vector3(0.f, 0.f, XM_PIDIV2));
			obj->SetName(L"SMILE");
			obj->GetComponent<Transform>()->SetScale(Vector3(1.0f, 1.0f, 1.0f));

			MeshRenderer* mr = obj->AddComponent<MeshRenderer>();

			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));

			Vector2 vec2(1.0f, 1.0f);
			mr->GetMaterial()->SetData(eGPUParam::Vector2, &vec2);

			PlayerScript* playerScript = obj->AddComponent<PlayerScript>();
		
		//SMILE RECT CHILD
			GameObject* child = object::Instantiate<GameObject>(eLayerType::Camera, obj->GetComponent<Transform>());
			child->SetName(L"SMILE");
			child->GetComponent<Transform>()->SetPosition(Vector3(1.0f, 1.0f, 1.0f));
			child->GetComponent<Transform>()->SetScale(Vector3(1.0f, 1.0f, 1.0f));

			MeshRenderer* childMr = child->AddComponent<MeshRenderer>();

			childMr->SetMaterial(Resources::Find<Material>(L"RectMaterial"));
			childMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		}

		//HPBAR
		{
			GameObject* hpBar = object::Instantiate<GameObject>(eLayerType::UI);
			hpBar->GetComponent<Transform>()->SetPosition(Vector3(1.0f, 1.0f, 1.0f));
			hpBar->GetComponent<Transform>()->SetScale(Vector3(1.0f, 1.0f, 1.0f));

			SpriteRenderer* hpBarSR = hpBar->AddComponent<SpriteRenderer>();

			//std::shared_ptr<Mesh> hpMesh = Resources::Find<Mesh>(L"RectMesh");
			//std::shared_ptr<Material> hpMaterial = Resources::Find<Material>(L"UIMaterial");
			//std::shared_ptr<Texture> hpTexture = Resources::Find<Texture>(L"UIMaterial");
			//hpMaterial->SetTexture(hpTexture);

			hpBarSR->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			hpBarSR->SetMaterial(Resources::Find<Material>(L"UIMaterial"));
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