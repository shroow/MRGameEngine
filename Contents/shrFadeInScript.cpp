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
		: Script(eScriptType::ObjectScript)
		, mStart(true)
		, mFadeIn(true)
		, mSpeed(2.f)
		, mAlpha(0.f)
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
		if (Input::GetKeyState(eKeyCode::P) == eKeyState::DOWN)
		{
			if (mStart)
				mStart = false;
			else
				mStart = true;
		}

		if (Input::GetKeyState(eKeyCode::F) == eKeyState::DOWN)
		{
			if (mFadeIn)
				mFadeIn = false;
			else
				mFadeIn = true;
		}

		//if (mStart)
		//{
		//	if (mFadeIn && mAlpha < 1.f)
		//		mAlpha += Time::DeltaTime() / mSpeed;
		//	else if(!mFadeIn && mAlpha > -1.f)
		//		mAlpha -= Time::DeltaTime() / mSpeed;
		//}

		if (mStart)
		{
			if (mFadeIn)
			{
				mAlpha += Time::DeltaTime() / mSpeed;
				if (mAlpha > 1.f)
					mFadeIn = false;
			}
			else 
			{
				mAlpha -= Time::DeltaTime() / mSpeed;
				if (mAlpha < -1.f)
					mFadeIn = true;
			}
		}

		//Constant buffer
		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::FadeIn];
		renderer::FadeInCB data;
		data.fAlpha = mAlpha;

		cb->SetData(&data);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);
	}

	void FadeInScript::FixedUpdate()
	{

	}

	void FadeInScript::Render()
	{
	}
}