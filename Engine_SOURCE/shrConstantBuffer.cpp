#include "shrConstantBuffer.h"
#include "shrGraphicDevice_DX11.h"


namespace shr::graphics
{
	ConstantBuffer::ConstantBuffer(eCBType type)
		: mType(type)
	{

	}

	ConstantBuffer::~ConstantBuffer()
	{
	}

	bool ConstantBuffer::Create(size_t size)
	{
		// 상수 버퍼
		desc.ByteWidth = size;
		desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		desc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;

		if (!GetDevice()->CreateBuffer(&desc, nullptr, buffer.GetAddressOf()))
			return false;

		return true;
	}

	void ConstantBuffer::Bind(void* data)
	{
		//ConstantBuffer->Create를 안해주면 
		//D3D11_MAPPED_SUBRESOURCE memcpy 시 에러
		GetDevice()->BindConstantBuffer(buffer.Get(), data, desc.ByteWidth);
	}

	void ConstantBuffer::SetPipline(eShaderStage stage)
	{
		GetDevice()->SetConstantBuffer(stage, mType, buffer.Get());
	}
}