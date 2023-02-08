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

		void AddGameObject(GameObject* gameObj, const eLayerType type);

	private:
		std::vector<Layer> mLayers;
	};
}
