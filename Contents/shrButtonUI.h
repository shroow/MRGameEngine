#pragma once
#include "shrUIBase.h"

namespace shr
{
	enum class eButtonUIState
	{
		Idle,
		Hovered,
		Pressed,
		Down,
	};


	class ButtonUI :
		public UIBase
	{
	public:
		ButtonUI();
		virtual ~ButtonUI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void UpdateState();

		void SetHovered(bool tf) { mIsHovered = tf; }
		bool GetHovered() { return mIsHovered; }

		void SetState(eButtonUIState state) { mState = state; }
		eButtonUIState GetState() { return mState; }

	protected:
		bool mIsHovered;
		eButtonUIState mState;

		std::function<void()> mClickCallback;

	private:
		class Collider2D* mButtonUICollider;
		class ButtonScript* mButtonScript;


	public:
		template<typename T>
		void SetClickCallback(T* obj, void (T::* func)())
		{
			mClickCallback = std::bind(func, obj);
		}

		void SetClickCallback(void (*func)())
		{
			mClickCallback = std::bind(func);
		}
	};
}
