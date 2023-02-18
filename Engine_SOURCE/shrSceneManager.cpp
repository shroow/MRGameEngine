#include "shrSceneManager.h"
#include "shrTransform.h"
#include "shrMeshRenderer.h"
#include "shrRenderer.h"
#include "shrResources.h"
#include "shrTexture.h"
#include "shrPlayerScript.h"
#include "shrCamera.h"
#include "shrCameraScript.h"
#include "shrSpriteRenderer.h"

namespace shr
{
	Scene* SceneManager::mPlayScene = nullptr;

	void SceneManager::Initialize()
	{
		mPlayScene = new Scene();
		mPlayScene->Initialize();

		//Camera Object
		GameObject* cameraObj = new GameObject();
		Transform* cameraTr = new Transform;
		cameraTr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		cameraObj->AddComponent(cameraTr);
		Camera* cameraComp = new Camera();
		cameraObj->AddComponent(cameraComp);
		CameraScript* cameraScript = new CameraScript();
		cameraObj->AddComponent(cameraScript);

		mPlayScene->AddGameObject(cameraObj, eLayerType::Camera);

		//Player Object SMILE
		GameObject* obj = new GameObject();
		Transform* tr = new Transform();
		tr->SetPosition(Vector3(0.0f, 0.0f, 11.0f));
		tr->SetScale(Vector3(5.0f, 5.0f, 1.0f));
		obj->AddComponent(tr);

		MeshRenderer* mr = new MeshRenderer();
		obj->AddComponent(mr);
		
		//머테리얼이 없어서 셰이더를 직접 지정해줄때 사용했다
		//Shader* shader = Resources::Find<Shader>(L"RectShader");
		
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> material = Resources::Find<Material>(L"RectMaterial");

		Vector2 vec2(1.0f, 1.0f);
		material->SetData(eGPUParam::Vector2, &vec2);

		mr->SetMaterial(material);
		mr->SetMesh(mesh);

		mPlayScene->AddGameObject(obj, eLayerType::Player);

		// SMILE RECT
		GameObject* spriteObj = new GameObject();
		Transform* spriteTr = new Transform();
		spriteTr->SetPosition(Vector3(0.0f, 0.0f, 10.0f));
		spriteTr->SetScale(Vector3(5.0f, 0.0f, 10.0f));
		spriteObj->AddComponent(spriteTr);
			
		SpriteRenderer* sr = new SpriteRenderer();
		spriteObj->AddComponent(sr);

		std::shared_ptr<Material> spriteMaterial = Resources::Find<Material>(L"SpriteMaterial");

		//Vector2 vec2(1.0f, 1.0f);
		//spriteMaterial->SetData(eGPUParam::Vector2, &vec2);

		sr->SetMaterial(spriteMaterial);
		sr->SetMesh(mesh);

		mPlayScene->AddGameObject(spriteObj, eLayerType::Player);
	}

	void SceneManager::Update()
	{
		mPlayScene->Update();
	}

	void SceneManager::FixedUpdate()
	{
		mPlayScene->FixedUpdate();
	}

	void SceneManager::Render()
	{
		mPlayScene->Render();
	}

	void SceneManager::Release()
	{
		delete mPlayScene;
		mPlayScene = nullptr;
	}
}