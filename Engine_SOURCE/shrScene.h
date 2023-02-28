#pragma once
#include "shrEntity.h"
#include "shrLayer.h"
#include "shrGameObject.h"

namespace shr
{
	using namespace shr::enums;
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		virtual void OnEnter();
		virtual void OnExit();

	public:
		virtual void LoadResources();

	
		void AddGameObject(GameObject* gameObj, const eLayerType type);
		Layer& GetLayerType(eLayerType type) { return mLayerVec[(UINT)type]; }
		std::vector<GameObject*> GetDontDestroyGameObjects();

	private:
		std::vector<Layer> mLayerVec;
	};
}
