#include "shrNoiseShader.h"


namespace shr::graphics
{
	NoiseShader::NoiseShader()
		: ComputeShader()
		, mTarget(nullptr)
	{
	}

	NoiseShader::~NoiseShader()
	{
	}

	void NoiseShader::Binds()
	{
		mTarget->BindUnorderedAccessView(0);

		mGroupX = mTarget->GetWidth() / mThreadGroupCountX + 1;
		mGroupY = mTarget->GetHeight() / mThreadGroupCountY + 1;
		mGroupZ = 1;
	}

	void NoiseShader::Clear()
	{
		mTarget->ClearUnorderedAccessView(0);
	}

}