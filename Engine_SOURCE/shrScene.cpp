#include "shrScene.h"


namespace shr
{
	Scene::Scene(eSceneType type)
		: mType(type)
	{
		mLayerVec.resize((UINT)eLayerType::End);
	}
	Scene::~Scene()
	{

	}
	void Scene::Initialize()
	{
		for (Layer& layer : mLayerVec)
		{
			layer.Initialize();
		}
	}
	void Scene::Update()
	{
		for (Layer& layer : mLayerVec)
		{
			layer.Update();
		}
	}
	void Scene::FixedUpdate()
	{
		for (Layer& layer : mLayerVec)
		{
			layer.FixedUpdate();
		}
	}
	void Scene::Render()
	{
		for (Layer& layer : mLayerVec)
		{
			layer.Render();
		}
	}
	void Scene::Destroy()
	{
		for (Layer& layer : mLayerVec)
		{
			layer.Destroy();
		}
	}

	void Scene::OnEnter()
	{
	}
	void Scene::OnExit()
	{
	}

	void Scene::AddGameObject(GameObject* gameObj, const eLayerType type)
	{
		mLayerVec[(UINT)type].AddGameObject(gameObj);
		gameObj->SetLayerType(type);
	}
	
	std::vector<GameObject*> Scene::GetDontDestroyGameObjects()
	{
		std::vector<GameObject*> gameObjects;
		for (Layer& layer : mLayerVec)
		{
			std::vector<GameObject*> dontGameObjs
				= layer.GetDontDestroyGameObjects();

			gameObjects.insert(gameObjects.end()
			, dontGameObjs.begin()
			, dontGameObjs.end());
		}

		return gameObjects;
	}
	const std::vector<GameObject*>& Scene::GetGameObjectVec(const eLayerType type)
	{
		return mLayerVec[(UINT)type].GetGameObjectVec();
	}
}
