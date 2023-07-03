#pragma once
#include "shrGameObject.h"
#include "shrMaterial.h"

namespace shr
{
	class UIBase :
		public GameObject
	{
	public:
		UIBase();
		UIBase(const UIBase& obj);
		virtual ~UIBase();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void UseUV(bool use) { mbUseUV = use; }
		void SetStartUV(const Vector2& uv) { mStartUV = uv; }
		void SetEndUV(const Vector2& uv) { mEndUV = uv; }

		class SpriteRenderer* GetRenderer() { return mUIRenderer; }
		void SetRenderer(class SpriteRenderer* renderer);


	protected:
		bool mbUseUV;
		Vector2 mStartUV;
		Vector2 mEndUV;

		class SpriteRenderer* mUIRenderer;
	};
}
