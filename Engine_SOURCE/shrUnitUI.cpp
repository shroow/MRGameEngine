#include "shrUnitUI.h"
#include "shrObject.h"
#include "shrSpriteRenderer.h"
#include "shrResources.h"

namespace shr
{
	UnitUI::UnitUI()
		: GameObject()
		, mHPBar(nullptr)
		, mMPBar(nullptr)
	{
	}

	UnitUI::~UnitUI()
	{
	}

	void UnitUI::Initialize()
	{
		GameObject::Initialize();

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector3(6.f, 6.f, 6.f));

		// HPBAR
		mHPBar = object::Instantiate<GameObject>(eLayerType::Monster);
		mHPBar->SetName(L"HPBAR");
		Transform* hpBarTR = mHPBar->GetComponent<Transform>();
		hpBarTR->SetParent(tr);
		hpBarTR->SetPosition(Vector3(0.0f, -0.60f, 0.0f));
		hpBarTR->SetScale(Vector3(0.75f, 0.14f, 1.0f));

		SpriteRenderer* hpsr = mHPBar->AddComponent<SpriteRenderer>();
		mHPBar->AddComponent(hpsr);
		std::shared_ptr<Mesh> hpmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> hpspriteMaterial = std::make_shared<Material>();
		std::shared_ptr<Texture> hpTex = Resources::Find<Texture>(L"RedBarTexture");
		std::shared_ptr<Shader> hpShader = Resources::Find<Shader>(L"UIShader");
		hpspriteMaterial->SetTexture(eTextureSlot::T0, hpTex);
		hpspriteMaterial->SetShader(hpShader);
		hpsr->SetMesh(hpmesh);
		hpsr->SetMaterial(hpspriteMaterial);

		// MPBAR
		mMPBar = object::Instantiate<GameObject>(eLayerType::Monster);
		mMPBar->SetName(L"MPBAR");
		Transform* mpBarTR = mMPBar->GetComponent<Transform>();
		mpBarTR->SetParent(tr);
		mpBarTR->SetPosition(Vector3(0.0f, -0.75f, 0.0f));
		mpBarTR->SetScale(Vector3(0.75f, 0.14f, 1.0f));

		SpriteRenderer* mpSR = mMPBar->AddComponent<SpriteRenderer>();
		mMPBar->AddComponent(mpSR);
		std::shared_ptr<Mesh> mpMesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> mpSpriteMaterial = std::make_shared<Material>();;
		std::shared_ptr<Texture> mpTex = Resources::Find<Texture>(L"BlueBarTexture");
		std::shared_ptr<Shader> mpShader = Resources::Find<Shader>(L"UIShader");
		mpSpriteMaterial->SetTexture(eTextureSlot::T0, mpTex);
		mpSpriteMaterial->SetShader(mpShader);
		mpSR->SetMesh(mpMesh);
		mpSR->SetMaterial(mpSpriteMaterial);
	}

	void UnitUI::Update()
	{
		GameObject::Update();
	}

	void UnitUI::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void UnitUI::Render()
	{
		GameObject::Render();
	}
}
