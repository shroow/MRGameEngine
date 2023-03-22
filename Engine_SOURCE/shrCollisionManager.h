#pragma once
#include "CommonInclude.h"
#include "shrCollider2D.h"


namespace shr
{
	union ColliderID
	{
		struct
		{
			UINT32 left;
			UINT32 right;
		};
		UINT64 id;
	};

	//	class Scene;
	class CollisionManager
	{
	public:
		static void Initialize();
		static void Update();
		static void FixedUpdate();
		static void Render();

		static void CollisionLayerCheck(eLayerType left, eLayerType right, bool enable = true);
		static void LayerCollision(class Scene* scene, eLayerType left, eLayerType right);
		static void ColliderCollision(Collider2D* left, Collider2D* right);
		static bool Intersect(Collider2D* left, Collider2D* right);

		static void MouseCollision(class Scene* scene);
		static bool MouseIntersect(Collider2D* collider);
		static void MouseCollisionLayerCheck(eLayerType type, bool enable = true);

	private:
		static std::bitset<(UINT)eLayerType::End> mLayerCollisionMatrix[(UINT)eLayerType::End];
		static std::map<UINT64, bool> mCollisionMap;
		static std::bitset<(UINT)eLayerType::End> mMouseLayerCollisionBit;
		static std::optional<UINT> mPrevMouseCollision;
	};
}