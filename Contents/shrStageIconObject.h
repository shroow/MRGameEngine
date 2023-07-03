#pragma once
#include "shrGameObject.h"

namespace shr
{
    class StageIconObject :
        public GameObject
    {
	public:
		StageIconObject();
		virtual ~StageIconObject();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void Die() override;

	public:
		void SetSelected(bool tf) { mIsSelected = tf; }
		bool IsSelected() { return mIsSelected; }

	private:
		bool mIsSelected;
		Vector2 mStageNum;
		class BaseWidgetUI* mStageDetail;
    };
}

