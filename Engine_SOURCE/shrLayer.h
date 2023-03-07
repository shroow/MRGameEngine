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
		virtual void Destroy();

		void AddGameObject(GameObject* gameObject);
		const std::vector<GameObject*>& GetGameObjectVec() { return mGameObjectVec; }
		std::vector<GameObject*> GetDontDestroyGameObjects();

	private:
		std::vector<GameObject*> mGameObjectVec;
	};
	typedef const std::vector<GameObject*>& GameObjectVec;
	typedef std::vector<GameObject*>::iterator GameObjectIter;
}
