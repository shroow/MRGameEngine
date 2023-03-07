#include "shrCameraScript.h"
#include "shrTransform.h"
#include "shrGameObject.h"
#include "shrInput.h"
#include "shrTime.h"

namespace shr
{
	CameraScript::CameraScript()
		: Script()
	{
	}

	CameraScript::~CameraScript()
	{
	}

	void CameraScript::Initialize()
	{
	}

	void CameraScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

		Vector3 pos = tr->GetPosition();

		if (Input::GetKeyState(eKeyCode::D) == eKeyState::PRESSED)
		{
			//pos.x += 3.0f * Time::DeltaTime();
			pos += 50.f * tr->Right() * Time::DeltaTime(); //축을 따라 이동
		}
		else if (Input::GetKeyState(eKeyCode::A) == eKeyState::PRESSED)
		{
			//pos.x -= 3.0f * Time::DeltaTime();
			pos += 50.f * -tr->Right() * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::W) == eKeyState::PRESSED)
		{
			//pos.z += 3.0f * Time::DeltaTime();
			pos += 50.f * tr->Foward() * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::S) == eKeyState::PRESSED)
		{
			//pos.z -= 3.0f * Time::DeltaTime();
			pos += 50.f * -tr->Foward() * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::Q) == eKeyState::PRESSED)
		{
			//pos.y -= 3.0f * Time::DeltaTime();
			pos += 50.f * tr->Up() * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::E) == eKeyState::PRESSED)
		{
			//pos.y += 3.0f * Time::DeltaTime();
			pos += 50.f * -tr->Up() * Time::DeltaTime();
		}

		tr->SetPosition(pos);
	}

	void CameraScript::Render()
	{
	}
}