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
				// �ش�Ű�� ���� �����ִ�.
				if (GetAsyncKeyState(ASCII[i]) & 0x8000)
				{
					// ���� �����ӿ��� ���� �־���.
					if (mKeys[i].bPressed)
						mKeys[i].eState = eKeyState::PRESSED;
					else
						mKeys[i].eState = eKeyState::DOWN;

					mKeys[i].bPressed = true;
				}
				else // �ش�Ű�� ���� �ȴ����ִ�.
				{
					// ���� �����ӿ��� ���� �־���.
					if (mKeys[i].bPressed)
						mKeys[i].eState = eKeyState::UP;
					else // ���� �����ӿ��� �ȴ��� �־���.
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

		Matrix view = renderer::mainCamera->GetViewMatrix();
		Matrix proj = renderer::mainCamera->GetProjectionMatrix();
		Matrix invViewProj = XMMatrixInverse(nullptr, view * proj);

		//���콺 ��ġ ����Ʈ ũ��� ����ȭ
		float x = (mousePos.x / screenWidth) * 2.0f - 1.f;
		float y = ((screenHeight - mousePos.y) / screenHeight) * 2.0f - 1.f;

		mMouse.pos.x = (float)mousePos.x;
		mMouse.pos.y = (float)mousePos.y;
		mMouse.move.x = mMouse.pos.x - mousePos.x;
		mMouse.move.y = mMouse.pos.y - mousePos.y;

		// Transform the mouse position from NDC space to world space
		XMVECTOR mouseTr = XMVectorSet(x, y, 1.f, 0.f);
		mouseTr = XMVector3TransformCoord(mouseTr, invViewProj);

		float x1 = XMVectorGetX(mouseTr);
		float y1 = XMVectorGetY(mouseTr);
		float z1 = XMVectorGetZ(mouseTr);
		float w1 = XMVectorGetW(mouseTr);

		std::wstring message;
		message = message + L"X:" + std::to_wstring(x1) + L", Y:" + std::to_wstring(y1)
			+ L", Z:" + std::to_wstring(z1) + L", W:" + std::to_wstring(w1) + L"\n";
		OutputDebugString(message.c_str());


		// Extract the position of the mouse in world space
		mMouse.worldPos.x = XMVectorGetX(mouseTr);
		mMouse.worldPos.y = XMVectorGetY(mouseTr);
	}
}