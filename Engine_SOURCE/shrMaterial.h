#pragma once

#include "shrResource.h"
#include "shrShader.h"
#include "shrRenderer.h"
//#include "shrConstantBuffer.h"

using namespace shr::renderer;
namespace shr::graphics
{
	class Material : public Resource
	{
	public:
		Material();
		~Material();

		virtual HRESULT Load(const std::wstring& path) override;

		void SetData(eGPUParam param, void* data);
		void Bind();

		void SetShader(Shader* shader) { mShader = shader; }
		Shader* GetShader() { return mShader; }

	private:
		Shader* mShader;
		MaterialCB mCB;
	};
}
