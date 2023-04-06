#pragma once
#include "..\External\DirectXTex\Include\DirectXTex.h"
#include "shrResource.h"
#include "shrGraphicDevice_DX11.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\External\\DirectXTex\\Lib\\Debug\\DirectXTex.lib") 
#else 
#pragma comment(lib, "..\\External\\DirectXTex\\Lib\\Release\\DirectXTex.lib") 
#endif

using namespace shr::enums;
namespace shr::graphics
{
	class Texture : 
		public Resource
	{
	public:
		Texture();
		virtual ~Texture();

		bool Create(UINT width, UINT height, DXGI_FORMAT format, UINT bindFlag);
		bool Create(Microsoft::WRL::ComPtr<ID3D11Texture2D> texture);
		virtual HRESULT Load(const std::wstring& path) override;
		void LoadFile(const std::wstring& fullPath);
		void InitializeResource();
		void BindShaderResource(eShaderStage stage, UINT slot);
		void BindUnorderedAccessView(UINT startSlot);
		void ClearUnorderedAccessView(UINT startSlot);

		void Clear();
		static void Clear(UINT startSlot);

		//size_t GetHeight() { return mImage.GetMetadata().height; }
		//size_t GetWidth() { return mImage.GetMetadata().width; }
		size_t GetHeight() { return mDesc.Height; }
		size_t GetWidth() { return mDesc.Width; }

		void SetTexture(Microsoft::WRL::ComPtr<ID3D11Texture2D> texture) { mTexture = texture; }

		Microsoft::WRL::ComPtr<ID3D11Texture2D> GetTexture() { return mTexture; }
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> GetDSV() { return mDSV; }
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> GetRTV() { return mRTV; }
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> GetUAV() { return mUAV; }
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetSRV() { return mSRV; }

	private:
		ScratchImage mImage;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mTexture;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDSV;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRTV;
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> mUAV;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;
		D3D11_TEXTURE2D_DESC mDesc;
	};
}
