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

		virtual void Start();
		
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
		virtual void Destroy();

		virtual void OnEnter();
		virtual void OnExit();

		eSceneType GetSceneType() { return mType; }
		void AddGameObject(GameObject* gameObj, const eLayerType type);
		Layer& GetLayer(eLayerType type) { return mLayerVec[(UINT)type]; }
		std::vector<GameObject*> GetDontDestroyGameObjects();
		const std::vector<GameObject*>& GetGameObjectVec(const eLayerType type);

		void SetCameraOn(bool tf) { mCameraOn = tf; }
		bool GetCameraOn() { return mCameraOn; }

		//Debug Check(SceneManager)
		std::vector<Layer> GetLayerVec() { return mLayerVec; }
		GameObject* GetMainCamera() { return mMainCamera; }

	protected:
		bool mStart;
		bool mCameraOn;
		GameObject* mMainCamera;

	private:
		std::vector<Layer> mLayerVec;
		eSceneType mType;
	};
}
