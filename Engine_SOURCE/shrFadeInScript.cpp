#include "shrFadeInScript.h"
#include "shrRenderer.h"
#include "shrGameObject.h"
#include "shrTransform.h"
#include "shrConstantBuffer.h"
#include "shrApplication.h"
#include "shrTime.h"
#include "shrTexture.h"
#include "shrInput.h"

extern shr::Application application;

namespace shr
{
	FadeInScript::FadeInScript()
		: Script()
		, mStart(false)
		, mFadeOut(0)
		, mSpeed(3.f)
		, mColor(Vector4(255.f, 255.f, 255.f, 1.f))
	{
	}

	FadeInScript::~FadeInScript()
	{
	}

	void FadeInScript::Initialize()
	{
	}

	void FadeInScript::Update()
	{
		float DeltaTime = Time::DeltaTime();
		float Time = DeltaTime / mSpeed;
		//Constant buffer
		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::FadeIn];
		renderer::FadeInCB data;
		data.iFadeOut = mFadeOut;
		data.fTime = Time;
		data.fadeColor = mColor;

		cb->Bind(&data);
		cb->SetPipline(eShaderStage::VS);
		cb->SetPipline(eShaderStage::PS);
	}

	void FadeInScript::FixedUpdate()
	{

	}

	void FadeInScript::Render()
	{
	}
}