#pragma once
#include "shrEntity.h"
#include "shrGraphics.h"

namespace shr::graphics
{
    class StructedBuffer :
        public GpuBuffer
    {
	public:
		StructedBuffer();
		~StructedBuffer();

		bool Create(UINT size, UINT stride, eSRVType type, void* data);
		void SetData(void* data, UINT bufferCount);
		void Bind(eShaderStage stage, UINT slot);


		UINT GetSize() { return mSize; }
		UINT GetStride() { return mStride; }

	private:
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;
		eSRVType mType;

		UINT mSize;
		UINT mStride;
    };
}

