#include "shrGameObject.h"
#include "shrTransform.h"

namespace shr
{
	GameObject::GameObject()
		: mState(eState::Active)
		, mLayerType(eLayerType::None)
		, mbDontDestroy(false)
	{
		mComponents.resize((UINT)eComponentType::End);
		AddComponent(new Transform());
	}

	GameObject::GameObject(const GameObject& obj)
		: Entity(obj)
	{
		mComponents.resize((UINT)eComponentType::End);
		Transform* tr = AddComponent<Transform>();

		Transform* objTr = obj.GetComponent<Transform>();

		tr->SetPosition(objTr->GetPosition());
		tr->SetRotation(objTr->GetRotation());
		tr->SetScale(objTr->GetScale());
	}

	GameObject::~GameObject()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			delete comp;
			comp = nullptr;
		}

		for (Component* scrComp : mScriptVec)
		{
			if (scrComp == nullptr)
				continue;

			delete scrComp;
			scrComp = nullptr;
		}
	}

	void GameObject::Initialize()
	{
		/*for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->Initialize();
		}

		for (Component* script : mScriptVec)
		{
			if (script == nullptr)
				continue;

			script->Initialize();
		}*/
	}

	void GameObject::Update()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->Update();
		}

		for (Component* script : mScriptVec)
		{
			if (script == nullptr)
				continue;

			script->Update();
		}
	}

	void GameObject::FixedUpdate()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->FixedUpdate();
		}

		for (Component* script : mScriptVec)
		{
			if (script == nullptr)
				continue;

			script->FixedUpdate();
		}
	}

	void GameObject::Render()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->Render();
		}

		for (Component* script : mScriptVec)
		{
			if (script == nullptr)
				continue;

			script->Render();
		}
	}

	void GameObject::AddComponent(Component* comp)
	{
		eComponentType order = comp->GetOrder();

		if (order != eComponentType::Script)
		{
			mComponents[(UINT)order] = comp;
			mComponents[(UINT)order]->SetOwner(this);
		}
		else
		{
			mScriptVec.push_back(dynamic_cast<Script*>(comp));
			comp->SetOwner(this);
		}
	}
}
