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
				donts.push_back(*iter);
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