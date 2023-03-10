#pragma once
#include "CommonInclude.h"
#include "shrMath.h"


namespace shr
{
	enum class eKeyCode
	{
		//Alphabet
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L, 
		Z, X, C, V, B, N, M,
		
		//Special Key
		ENTER, ESC, LSHIFT, LALT, LCTRL,
		SPACE, LEFT, RIGHT, UP, DOWN,
		LBTN, RBTN,
		
		//Num Pad
		NUM_0, NUM_1, NUM_2,
		NUM_3, NUM_4, NUM_5,
		NUM_6, NUM_7, NUM_8,
		NUM_9,

		//Num Line
		N_0, N_1, N_2, N_3, N_4, N_5,
		N_6, N_7, N_8, N_9,
		
		END,
	};
	enum eKeyState
	{
		DOWN,
		PRESSED,
		UP,
		NONE,
	};

	class Input
	{
	public:
		struct Key
		{
			eKeyCode  eType;
			eKeyState eState;
			bool	  bPressed;
		};

		struct Mouse
		{
			eKeyState eLState;
			eKeyState eRState;

			bool	  bLPressed;
			bool	  bRPressed;

			math::Vector2 mPos;
			math::Vector2 mMove;
			math::Vector2 mWorldPos;
		};

		static void Initialize();
		static void Update();

		static __forceinline eKeyState GetKeyState(eKeyCode keyCode) 
		{ 
			return mKeys[static_cast<UINT>(keyCode)].eState; 
		}

		static __forceinline bool GetKey(eKeyCode keyCode)
		{
			return mKeys[static_cast<UINT>(keyCode)].eState == eKeyState::PRESSED;
		}

		static __forceinline bool GetKeyDown(eKeyCode keyCode)
		{
			return mKeys[static_cast<UINT>(keyCode)].eState == eKeyState::DOWN;
		}

		static __forceinline bool GetKeyUp(eKeyCode keyCode)
		{
			return mKeys[static_cast<UINT>(keyCode)].eState == eKeyState::UP;
		}

		//Mouse Functions
		static __forceinline Mouse GetMouse(Mouse& mouse)
		{
			mouse.bLPressed = mMouse.bLPressed;
			mouse.bRPressed = mMouse.bRPressed;
			mouse.eLState = mMouse.eLState;
			mouse.eRState = mMouse.eRState;
			mouse.mMove = mMouse.mMove;
			mouse.mPos = mMouse.mPos;
			mouse.mWorldPos = mMouse.mWorldPos;
		}

		static __forceinline math::Vector2 GetMousePos()
		{
			return mMouse.mPos;
		}

		static __forceinline math::Vector2 GetMouseWorldPos()
		{
			return mMouse.mWorldPos;
		}

		static __forceinline math::Vector2 GetMouseMove()
		{
			return mMouse.mMove;
		}

		static __forceinline bool GetMouseLeftPressed()
		{
			return mMouse.eLState == eKeyState::PRESSED;
		}
		static __forceinline bool GetMouseLeftDown()
		{
			return mMouse.eLState == eKeyState::DOWN;
		}
		static __forceinline bool GetMouseLeftUp()
		{
			return mMouse.eLState == eKeyState::UP;
		}

		static __forceinline bool GetMouseRightPressed()
		{
			return mMouse.eLState == eKeyState::PRESSED;
		}
		static __forceinline bool GetMouseRightDown()
		{
			return mMouse.eLState == eKeyState::DOWN;
		}
		static __forceinline bool GetMouseRightUp()
		{
			return mMouse.eLState == eKeyState::UP;
		}

	private:
		Input() = delete;
		~Input() = delete;

	private:
		static std::vector<Key> mKeys;
		static Mouse mMouse;
	};
}
