#pragma once
#include "shrGameObject.h"

namespace shr
{
	class Layer : public Entity
	{
	public:
		Layer();
		virtual ~Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void AddGameObject(GameObject* gameObject);
		const std::vector<GameObject*>& GetVecGameObjects() { return mVecGameObjects; }

	private:
		std::vector<GameObject*> mVecGameObjects;
	};
	typedef const std::vector<GameObject*>& GameObjects;
}
