#include "shrInput.h"
#include "shrApplication.h"
#include "shrRenderer.h"


extern shr::Application application;
namespace shr
{
	std::vector<Input::Key> Input::mKeys;
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

			mKeys.push_back(key);
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
					if (mKeys[i].bPressed)
						mKeys[i].eState = eKeyState::PRESSED;
					else
						mKeys[i].eState = eKeyState::DOWN;

					mKeys[i].bPressed = true;
				}
				else // 해당키가 현재 안눌려있다.
				{
					// 이전 프레임에는 눌려 있었다.
					if (mKeys[i].bPressed)
						mKeys[i].eState = eKeyState::UP;
					else // 이전 프레임에도 안눌려 있었다.
						mKeys[i].eState = eKeyState::NONE;

					mKeys[i].bPressed = false;
				}
			}
			
			//ComputeMousePos();

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
				if (eKeyState::DOWN == mKeys[i].eState || eKeyState::PRESSED == mKeys[i].eState)
					mKeys[i].eState = eKeyState::UP;
				else if (eKeyState::UP == mKeys[i].eState)
					mKeys[i].eState = eKeyState::NONE;

				mKeys[i].bPressed = false;
			}
		}

	}

	void Input::ComputeMousePos()
	{
		POINT mousePos = {};
		GetCursorPos(&mousePos);
		ScreenToClient(application.GetHwnd(), &mousePos);

		RECT winRect = {};
		GetClientRect(application.GetHwnd(), &winRect);

		//GetResolutionRatio
		float screenWidth = (float)winRect.right - (float)winRect.left;
		float screenHeight = (float)winRect.bottom - (float)winRect.top;
		float resolutionRatio = screenWidth / screenHeight;

		//마우스 위치 뷰포트 크기로 정규화
		float x = (mousePos.x / screenWidth) * 2.0f - 1.f;
		float y = ((screenHeight - mousePos.y) / screenHeight) * 2.0f - 1.f;

		mMouse.pos.x = (float)mousePos.x;
		mMouse.pos.y = (float)mousePos.y;
		mMouse.move.x = mMouse.pos.x - mousePos.x;
		mMouse.move.y = mMouse.pos.y - mousePos.y;



		Matrix view = renderer::mainCamera->GetViewMatrix();
		Matrix proj = renderer::mainCamera->GetProjectionMatrix();

		Matrix invViewProj = XMMatrixInverse(nullptr, view * proj);

		// Transform the mouse position from NDC space to world space
		XMVECTOR mouseTr = XMVectorSet(x, y, 0.f, 1.f);
		mouseTr = XMVector3TransformCoord(mouseTr, invViewProj);

		float x1 = XMVectorGetX(mouseTr);
		float y1 = XMVectorGetY(mouseTr);
		float z1 = XMVectorGetZ(mouseTr);
		float w1 = XMVectorGetW(mouseTr);

		// Extract the position of the mouse in world space
		mMouse.worldPos.x = XMVectorGetX(mouseTr);
		mMouse.worldPos.y = XMVectorGetY(mouseTr);


		//Matrix invView = XMMatrixInverse(nullptr, view);
		//Matrix invProj = XMMatrixInverse(nullptr, proj);

		//Matrix mouseProj = {};
		//mouseProj._11 = 1.f;
		//mouseProj._22 = 1.f;
		//mouseProj._33 = 1.f;
		//mouseProj._44 = 1.f;
		//mouseProj._41 = x;
		//mouseProj._42 = y;
		//mouseProj._43 = 1.f;

		//Matrix mouseView = mouseProj * invProj;
		//Matrix mouseWorld = mouseView * invView;

		//mMouse.worldPos.x = mouseWorld._11;
		//mMouse.worldPos.y = mouseWorld._22;
	}
}