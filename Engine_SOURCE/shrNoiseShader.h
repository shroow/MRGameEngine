#pragma once
#include "shrComputeShader.h"
#include "shrTexture.h"

namespace shr::graphics
{
	class NoiseShader : public ComputeShader
	{
	public:
		NoiseShader();
		~NoiseShader();

		virtual void Binds() override;
		virtual void Clear() override;

		void SetTarget(std::shared_ptr<Texture> texture) { mTarget = texture; }

	private:
		std::shared_ptr<Texture> mTarget;
	};
}
