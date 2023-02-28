#include "shrInput.h"
#include "shrApplication.h"


extern shr::Application application;
namespace shr
{
	std::vector<Input::Key> Input::mKeyVec;
	Input::Mouse Input::mMouse;
	int ASCII[(UINT)eKeyCode::END] =
	{
		//Alphabet
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',
		
		//Special Key
		VK_RETURN, VK_ESCAPE, VK_LSHIFT, VK_LMENU, VK_LCONTROL,
		VK_SPACE, VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN,
		VK_LBUTTON, VK_RBUTTON,

		//Num Pad
		VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2,
		VK_NUMPAD3, VK_NUMPAD4, VK_NUMPAD5,
		VK_NUMPAD6, VK_NUMPAD7, VK_NUMPAD8,
		VK_NUMPAD9,

		//Num Line
		'0', '1', '2', '3', '4', '5',
		'6', '7', '8', '9',
	};
	

	void Input::Initialize()
	{
		for (UINT i = 0; i < (UINT)eKeyCode::END; i++)
		{
			Key key;
			key.eType = (eKeyCode)i;
			key.eState = eKeyState::NONE;
			key.bPressed = false;

			mKeyVec.push_back(key);
		}
	}

	void Input::Update()
	{
		if (GetFocus())
		{
			//KEY
			for (UINT i = 0; i < (UINT)eKeyCode::END; ++i)
			{
				// 해당키가 현재 눌려있다.
				if (GetAsyncKeyState(ASCII[i]) & 0x8000)
				{
					// 이전 프레임에도 눌려 있었다.
					if (mKeyVec[i].bPressed)
						mKeyVec[i].eState = eKeyState::PRESSED;
					else
						mKeyVec[i].eState = eKeyState::DOWN;

					mKeyVec[i].bPressed = true;
				}
				else // 해당키가 현재 안눌려있다.
				{
					// 이전 프레임에는 눌려 있었다.
					if (mKeyVec[i].bPressed)
						mKeyVec[i].eState = eKeyState::UP;
					else // 이전 프레임에도 안눌려 있었다.
						mKeyVec[i].eState = eKeyState::NONE;

					mKeyVec[i].bPressed = false;
				}
			}
			
			POINT mousePos = {};
			GetCursorPos(&mousePos);
			ScreenToClient(application.GetHwnd(), &mousePos);
			//GetResolutionRatio
			mMouse.mMove.x = mousePos.x - mMouse.mPos.x;
			mMouse.mMove.y = mousePos.y - mMouse.mPos.y;
			mMouse.mPos.x = mousePos.x;
			mMouse.mPos.y = mousePos.y;

			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			{
				if (mMouse.bLPressed)
					mMouse.eLState = eKeyState::PRESSED;
				else
					mMouse.eLState = eKeyState::DOWN;

				mMouse.bLPressed = true;
			}
			else
			{
				if (mMouse.bLPressed)
					mMouse.eLState = eKeyState::UP;
				else 
					mMouse.eLState = eKeyState::NONE;

				mMouse.bLPressed = false;
			}

			if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
			{
				if (mMouse.bRPressed)
					mMouse.eRState = eKeyState::PRESSED;
				else
					mMouse.eRState = eKeyState::DOWN;

				mMouse.bRPressed = true;
			}
			else
			{
				if (mMouse.bRPressed)
					mMouse.eRState = eKeyState::UP;
				else
					mMouse.eRState = eKeyState::NONE;

				mMouse.bRPressed = false;
			}
		}
		else
		{
			for (UINT i = 0; i < (UINT)eKeyCode::END; ++i)
			{
				if (eKeyState::DOWN == mKeyVec[i].eState || eKeyState::PRESSED == mKeyVec[i].eState)
					mKeyVec[i].eState = eKeyState::UP;
				else if (eKeyState::UP == mKeyVec[i].eState)
					mKeyVec[i].eState = eKeyState::NONE;

				mKeyVec[i].bPressed = false;
			}
		}

	}
}