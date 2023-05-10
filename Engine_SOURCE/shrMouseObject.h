#pragma once
#include "shrGameObject.h"

namespace shr
{
    class MouseObject :
        public GameObject
    {
    public:
		MouseObject();
		virtual ~MouseObject();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	public:
		bool IsSelected() { return mIsSelected; }

		void UnitDeSelected() { mSelectedUnit = nullptr; mIsSelected = false; }
		void UnitSelected(class UnitObject* obj) { mSelectedUnit = obj; mIsSelected = true; }
		class UnitObject* GetSelectedUnit() { return mSelectedUnit; }

	private:
		bool mIsSelected;
		class UnitObject* mSelectedUnit;
    };
}
