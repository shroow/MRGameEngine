#include "shrLayer.h"
#include "shrRenderer.h"
#include "shrTransform.h"

namespace shr
{
	// z값 정렬 작성중
	//static bool CompareGameObjectByZAxis(GameObject* a, GameObject* b)
	//{
	//	Transform* aTr = a->GetComponent<Transform>();
	//	Transform* bTr = b->GetComponent<Transform>();

	//	if (aTr->GetPosition().z <= bTr->GetPosition().z)
	//	{
	//		return true;
	//	}

	//	return false;
	//}
	
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
		/*for (GameObject* obj : mGameObjectVec)
		{
			if (obj == nullptr)
				continue;

			obj->Initialize();
		}*/
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

		// sort z axis
		//std::vector<GameObject*> mGameObjects;
		//std::sort(mGameObjects.begin(), mGameObjects.end(), CompareGameObjectByZAxis);
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
			if ((*iter)->IsDontDestroy() == true)
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

	static bool SortVecYZ(const GameObject* a, const GameObject* b)
	{
		Transform* aTR = a->GetComponent<Transform>();
		Transform* bTR = a->GetComponent<Transform>();

		Vector3 aPos = aTR->GetPosition();
		Vector3 bPos = bTR->GetPosition();

		if (aPos.z != bPos.z)
			return aPos.z < bPos.z;
		else
			return aPos.y < bPos.y;
	}

	void Layer::SortLayerVec()
	{
		std::sort(mGameObjectVec.begin(), mGameObjectVec.end(), SortVecYZ);
	}
}