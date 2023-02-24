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
#include "shrFadeInScript.h"
#include "shrInput.h"

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
			GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera);
			Camera* cameraComp = cameraObj->AddComponent<Camera>();
			cameraComp->RegisterCameraInRenderer();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			cameraObj->AddComponent<CameraScript>();
		}

		//UI CameraObj
		{
			GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera);
			Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
			cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
			cameraUIComp->DisableLayerMasks();
			cameraUIComp->TurnLayerMask(eLayerType::UI, true);
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
			GameObject* hpBar = object::Instantiate<GameObject>(eLayerType::Player);
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
			GameObject* fadeinObject = object::Instantiate<GameObject>(eLayerType::Player);
			fadeinObject->SetName(L"FadeIn");
			Transform* fadeinTR = fadeinObject->GetComponent<Transform>();
			fadeinTR->SetPosition(Vector3(1.0f, 1.0f, 3.0f));
			fadeinTR->SetScale(Vector3(1.0f, 1.0f, 1.0f));

			SpriteRenderer* fadeinSR = fadeinObject->AddComponent<SpriteRenderer>();

			std::shared_ptr<Mesh> fadeinmesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> fadeinMaterial = Resources::Find<Material>(L"FadeInMaterial");
			fadeinSR->SetMesh(fadeinmesh);
			fadeinSR->SetMaterial(fadeinMaterial);
			fadeinObject->AddComponent<FadeInScript>();
		}

		mActiveScene->Initialize();
	}

	void SceneManager::Update()
	{
		
		//if (Input::GetKeyState(eKeyCode::F) == eKeyState::DOWN)


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