#pragma once
#include "shrEntity.h"
#include "shrComponent.h"
#include "shrScript.h"

namespace shr
{
	class GameObject : public Entity
	{
	public:
		enum eState
		{
			Active,
			Paused,
			Dead,
		};

		GameObject();
		GameObject(const GameObject& obj);
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();


		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();
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

			comp->Initialize();

			return comp;
		}

		void AddComponent(Component* comp);

		template <typename T>
		T* GetComponent() const
		{
			T* comp;
			for (auto c : mComponents)
			{
				comp = dynamic_cast<T*>(c);

				if (comp != nullptr)
					return comp;
			}

			return nullptr;
		}

		template <typename T>
		std::vector<T*> GetComponents()
		{
			std::vector<T*> components = {};

			T* comp;
			for (auto c : mComponents)
			{
				comp = dynamic_cast<T*>(c);

				if (comp != nullptr)
					components.push_back(comp);
			}

			return components;
		}

		template <typename T>
		T* GetScript() const
		{
			T* scirpt;
			for (auto c : mScriptVec)
			{
				scirpt = dynamic_cast<T*>(c);

				if (scirpt != nullptr)
					return scirpt;
			}

			return nullptr;
		}


		const std::vector<Script*>& GetScriptVec() { return mScriptVec; }

		eState GetState() { return mState; }
		bool IsPaused() { return mState == eState::Paused ? true : false; }
		bool IsDead() { return mState == eState::Dead ? true : false; }
		void Pause() { mState = eState::Paused; }
		virtual void Die() { mState = eState::Dead; }

		bool IsDontDestroy() { return mbDontDestroy; }
		void DontDestroy(bool TF) { mbDontDestroy = TF; }
		eLayerType GetLayerType() { return mLayerType; }
		void SetLayerType(eLayerType type) { mLayerType = type; }

	protected:
		std::vector<Component*> mComponents; //private -> protected

	private:
		eState mState;
		eLayerType mLayerType;
		std::vector<Script*> mScriptVec;
		bool mbDontDestroy;
	};
}
