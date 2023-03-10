#include "shrLayer.h"


namespace shr
{
	Layer::Layer()
	{
	}

	Layer::~Layer()
	{
		for (GameObject* obj : mGameObjectVec)
		{
			if (obj == nullptr)
				continue;

			delete obj;
			obj = nullptr;
		}
	}

	void Layer::Initialize()
	{
		for (GameObject* obj : mGameObjectVec)
		{
			if (obj == nullptr)
				continue;

			obj->Initialize();
		}
	}

	void Layer::Update()
	{
		for (GameObject* obj : mGameObjectVec)
		{
			if (obj == nullptr)
				continue;
			if (obj->GetState() != GameObject::eState::Active)
				continue;

			obj->Update();
		}
	}

	void Layer::FixedUpdate()
	{
		for (GameObject* obj : mGameObjectVec)
		{
			if (obj == nullptr)
				continue;
			if (obj->GetState() != GameObject::eState::Active)
				continue;

			obj->FixedUpdate();
		}
	}

	void Layer::Render()
	{
		for (GameObject* obj : mGameObjectVec)
		{
			if (obj == nullptr)
				continue;
			if (obj->GetState() != GameObject::eState::Active)
				continue;

			obj->Render();
		}
	}

	void Layer::Destroy()
	{
		std::set<GameObject*> deleteObjects;

		for (GameObject* gameObj : mGameObjectVec)
		{
			if (gameObj->GetState() == GameObject::eState::Dead)
				deleteObjects.insert(gameObj);
		}

		for (GameObjectIter iter = mGameObjectVec.begin()
			; iter != mGameObjectVec.end()
			; )
		{
			std::set<GameObject*>::iterator deleteIter
				= deleteObjects.find(*iter);

			if (deleteIter != deleteObjects.end())
				iter = mGameObjectVec.erase(iter);
			else
				iter++;
		}	

		for (GameObject* gameObj : deleteObjects)
		{
			delete gameObj;
			gameObj = nullptr;
		}
	}

	void Layer::AddGameObject(GameObject* gameObject)
	{
		if (gameObject == nullptr)
			return;

		mGameObjectVec.push_back(gameObject);
	}
	std::vector<GameObject*> Layer::GetDontDestroyGameObjects()
	{
		std::vector<GameObject*> donts;

		for (GameObjectIter iter = mGameObjectVec.begin()
			; iter != mGameObjectVec.end()
			;)
		{
			if ((*iter)->IsDontDestroy())
			{
				donts.push_back((*iter));
				iter = mGameObjectVec.erase(iter);
			}
			else
			{
				iter++;
			}
		}

		return donts;
	}
}