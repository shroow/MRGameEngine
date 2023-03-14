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
		, mOwnerTR(nullptr)
		, mIdle(false)
		, mDie(false)
		, mAttack(false)
		, mChange(false)
		, mHP(0.f)
		, mMaxHP(100.f)
	{
	}

	BikerScript::~BikerScript()
	{
		mOwnerTR = nullptr;
	}

	void BikerScript::Initialize()
	{
		LoadResources();

		mOwnerTR = GetOwner()->GetComponent<Transform>();
		//if(mOwnerTR)
		//	mOwnerTR->SetScale(Vector3(4.0f, 1.0f, 1.0f));

		mIdle = true;
		mHP = mMaxHP;
	}

	void BikerScript::Update()
	{
		if (mOwnerTR == nullptr)
		{
			mOwnerTR = GetOwner()->GetComponent<Transform>();
			if (mOwnerTR == nullptr)
				return;
		}

		if (Input::GetKeyState(eKeyCode::T) == eKeyState::PRESSED)
		{
			Vector3 rot = mOwnerTR->GetRotation();
			rot.z += 10.0f * Time::DeltaTime();
			mOwnerTR->SetRotation(rot);
		}

		Vector3 pos = mOwnerTR->GetPosition();

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

		//if (Input::GetMouseLeftPressed())
		//{
		//	Vector2 mousePos = Input::GetMouseWorldPos();
		//	
		//	Vector2 myPos(pos.x, pos.y);
		//	//myPos.Normalize();
		//	//Vector2 movePos(mousePos.x, mousePos.y);
		//	//movePos.Normalize();

		//	float dot = myPos.Dot(mousePos);

		//	float angle = acos(dot / (myPos.Length() * mousePos.Length()));
		//	
		//	pos.x += 3.0f * cos(angle) * Time::DeltaTime();
		//	pos.y += 3.0f * sin(angle) * Time::DeltaTime();;
		//}

		if (mHP <= 0.f)
		{
			mIdle = false;
			mAttack = false;
			mDie = true;
			mChange = true;
		}

		mOwnerTR->SetPosition(pos);
	}

	void BikerScript::FixedUpdate()
	{
		if (!mChange)
			return;

		if (mIdle)
		{
			std::shared_ptr<Material> material
				= Resources::Find<Material>(L"Biker_Idle_Material");
			if (material == nullptr)
				return;
			GetOwner()->GetComponent<SpriteRenderer>()->SetMaterial(material);

			mChange = false;
		}
		else if (mAttack)
		{
			std::shared_ptr<Material> material
				= Resources::Find<Material>(L"Biker_Attack3_Material");
			if (material == nullptr)
				return;
			GetOwner()->GetComponent<SpriteRenderer>()->SetMaterial(material);

			mChange = false;
		}
		else if (mDie)
		{
			std::shared_ptr<Material> material
				= Resources::Find<Material>(L"Biker_Death_Material");
			if (material == nullptr)
				return;
			GetOwner()->GetComponent<SpriteRenderer>()->SetMaterial(material);

			mChange = false;
		}
	}

	void BikerScript::Render()
	{
	}

	void BikerScript::LoadResources()
	{
		
	}

	void BikerScript::OnCollisionEnter(Collider2D* collider)
	{
		if (mDie)
			return;

		if (!mAttack)
		{
			mAttack = true;
			mIdle = false;
			mChange = true;
		}
	}
	void BikerScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void BikerScript::OnCollisionExit(Collider2D* collider)
	{
		if (mDie)
			return;

		if (!mIdle)
		{
			mIdle = true;
			mAttack = false;
			mChange = true;
		}
	}
	void BikerScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void BikerScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void BikerScript::OnTriggerExit(Collider2D* collider)
	{
	}
}