#include "shrBikerScript.h"
#include "shrGameObject.h"
#include "shrTransform.h"
#include "shrTime.h"
#include "shrInput.h"
#include "shrSpriteRenderer.h"
#include "shrFadeInScript.h"
#include "shrResources.h"

namespace shr
{
	BikerScript::BikerScript()
		: Script()
	{
	}

	BikerScript::~BikerScript()
	{
	}

	void BikerScript::Initialize()
	{
		Transform* bikerTR = GetOwner()->GetComponent<Transform>();
		bikerTR->SetPosition(Vector3(3.0f, 3.0f, 3.0f));
		bikerTR->SetScale(Vector3(3.0f, 3.0f, 3.0f));

		SpriteRenderer* BikerSR = GetOwner()->AddComponent<SpriteRenderer>();

		std::shared_ptr<Mesh> bikerMesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> bikerMaterial = Resources::Find<Material>(L"SpriteMaterial");
		std::shared_ptr<Texture> bikerTexture = Resources::Find<Texture>(L"Biker_Idle");
		bikerMaterial->SetTexture(bikerTexture);
	}

	void BikerScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

		if (Input::GetKeyState(eKeyCode::T) == eKeyState::PRESSED)
		{
			Vector3 rot = tr->GetRotation();
			rot.z += 10.0f * Time::DeltaTime();
			tr->SetRotation(rot);
		}

		Vector3 pos = tr->GetPosition();

		if (Input::GetKeyState(eKeyCode::RIGHT) == eKeyState::PRESSED)
		{
			pos.x += 3.0f * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::LEFT) == eKeyState::PRESSED)
		{
			pos.x -= 3.0f * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::DOWN) == eKeyState::PRESSED)
		{
			pos.y -= 3.0f * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::UP) == eKeyState::PRESSED)
		{
			pos.y += 3.0f * Time::DeltaTime();
		}

		tr->SetPosition(pos);
	}

	void BikerScript::FixedUpdate()
	{
	}

	void BikerScript::Render()
	{
	}
}