#pragma once
#include "shrScene.h"
#include "shrLayer.h"
#include "shrGameObject.h"
#include "shrSceneManager.h"
#include "shrTransform.h"

namespace shr::object
{
	template <typename T>
	static T* Instantiate(enums::eLayerType type)
	{
		T* gameObj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		Layer& layer = scene->GetLayer(type);
		layer.AddGameObject(gameObj);

		return gameObj;
	}

	template <typename T>
	static T* Instantiate(enums::eLayerType type, Transform* parent)
	{
		T* gameObj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		Layer& layer = scene->GetLayer(type);
		layer.AddGameObject(gameObj);

		Transform* tr = gameObj->GameObject::GetComponent<Transform>();
		tr->SetParent(parent);

		return gameObj;
	}

	template <typename T>
	static T* Instantiate(enums::eLayerType type, Vector3 position, Vector3 rotation)
	{
		T* gameObj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		Layer& layer = scene->GetLayer(type);
		layer.AddGameObject(gameObj);

		Transform* tr = gameObj->GameObject::GetComponent<Transform>();
		tr->SetPosition(position);
		tr->SetRotation(rotation);

		return gameObj;
	}

	template <typename T>
	static T* Instantiate(enums::eLayerType type, Vector3 position, Vector3 rotation, Transform* parent)
	{
		T* gameObj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		Layer& layer = scene->GetLayer(type);
		layer.AddGameObject(gameObj);

		Transform* tr = gameObj->GameObject::GetComponent<Transform>();
		tr->SetPosition(position);
		tr->SetRotation(rotation);
		tr->SetParent(parent);

		return gameObj;
	}

	void Destroy(GameObject* gameObject)
	{
		gameObject->Die();
	}
}