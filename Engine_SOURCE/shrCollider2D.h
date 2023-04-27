#pragma once
#include "shrComponent.h"
#include "shrTransform.h"

namespace shr
{
	class Collider2D : 
		public Component
	{
	public:
		Collider2D();
		Collider2D(eComponentType type);
		~Collider2D();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider);
		virtual void OnCollisionStay(Collider2D* collider);
		virtual void OnCollisionExit(Collider2D* collider);

		virtual void OnTriggerEnter(Collider2D* collider);
		virtual void OnTriggerStay(Collider2D* collider);
		virtual void OnTriggerExit(Collider2D* collider);


		bool IsTrigger() { return mbTrigger; }
		
		void SetType(eColliderType type) { mType = type; }
		void SetSize(Vector2 size) { mSize = size; }
		void SetCenter(Vector2 center) { mCenter = center; }
		void SetRadius(float radius) { mRadius = radius; }

		eColliderType GetType() { return mType; }
		Vector2 GetSize() { return mSize; }
		Vector2 GetCenter() { return mCenter; }
		UINT GetID() { return mID; }
		Vector3 GetPosition() { return mPosition; }
		Vector3 GetRotation() { return mRotation; }
		float GetRadius() { return mRadius; }

		virtual void OnMouseCollisionEnter();
		virtual void OnMouseCollisionStay();
		virtual void OnMouseCollisionExit();

	private:
		static UINT ColliderNumber;
		UINT mID;

		eColliderType mType;
		Transform* mTransform;

		Vector2 mSize;
		Vector2 mCenter;
		Vector3 mPosition;
		Vector3 mRotation;
		float mRadius;
		bool mbTrigger;
	};
}
