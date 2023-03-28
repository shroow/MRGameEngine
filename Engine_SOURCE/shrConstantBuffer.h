#pragma once
#include "shrGraphics.h"

using namespace shr::enums;

namespace shr::graphics
{
	class ConstantBuffer : GpuBuffer
	{
	public:
		ConstantBuffer(eCBType type);
		virtual ~ConstantBuffer();

		bool Create(size_t size);
		void SetData(void* data); //Bind
		void Bind(eShaderStage stage); //SetPipeline

	private:
		const eCBType mType;
	};
}
