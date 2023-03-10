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
		Scene(eSceneType type);
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
		virtual void Destroy();

		virtual void OnEnter();
		virtual void OnExit();

		eSceneType GetSceneType() { return mType; }
		void AddGameObject(GameObject* gameObj, const eLayerType type);
		Layer& GetLayerType(eLayerType type) { return mLayerVec[(UINT)type]; }
		std::vector<GameObject*> GetDontDestroyGameObjects();
		const std::vector<GameObject*>& GetGameObjectVec(const eLayerType type);

	public:
		virtual void LoadResources() {};

	private:
		std::vector<Layer> mLayerVec;
		eSceneType mType;
	};
}
