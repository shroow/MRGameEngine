#include "shrMaterial.h"

namespace shr::graphics
{
    Material::Material()
        : Resource(eResourceType::Material)
        , mMode(eRenderingMode::Opaque)
    {

    }

    Material::~Material()
    {
    }

    HRESULT Material::Load(const std::wstring& path)
    {



        return E_NOTIMPL;
    }

    void Material::SetData(eGPUParam param, void* data)
    {
        switch (param)
        {
        case shr::graphics::eGPUParam::Int_1:
            mCB.iData_1 = *static_cast<int*>(data);
            break;
        case shr::graphics::eGPUParam::Int_2:
            mCB.iData_2 = *static_cast<int*>(data);
            break;
        case shr::graphics::eGPUParam::Float_1:
            mCB.fData_1 = *static_cast<float*>(data);
            break;
        case shr::graphics::eGPUParam::Float_2:
            mCB.fData_2 = *static_cast<float*>(data);
            break;
        case shr::graphics::eGPUParam::Vector2_1:
            mCB.xy_1 = *static_cast<Vector2*>(data);
            break;
        case shr::graphics::eGPUParam::Vector2_2:
            mCB.xy_2 = *static_cast<Vector2*>(data);
            break;
        case shr::graphics::eGPUParam::Vector3_1:
            mCB.xyz_1 = *static_cast<Vector3*>(data);
            break;
        case shr::graphics::eGPUParam::Vector3_2:
            mCB.xyz_2 = *static_cast<Vector3*>(data);
            break;
        case shr::graphics::eGPUParam::Vector4:
            mCB.xyzw = *static_cast<Vector4*>(data);
            break;
        case shr::graphics::eGPUParam::Matrix:
            mCB.matrix = *static_cast<Matrix*>(data);
            break;
        default:
            break;
        }

    }

    void Material::Bind()
    {
        for (size_t i = 0; i < (UINT)eTextureSlot::End; i++)
        {
            if (mTexture[i] == nullptr)
                continue;

            mTexture[i]->BindShaderResource(eShaderStage::VS, (UINT)i);
            mTexture[i]->BindShaderResource(eShaderStage::HS, (UINT)i);
            mTexture[i]->BindShaderResource(eShaderStage::DS, (UINT)i);
            mTexture[i]->BindShaderResource(eShaderStage::GS, (UINT)i);
            mTexture[i]->BindShaderResource(eShaderStage::PS, (UINT)i);
            mTexture[i]->BindShaderResource(eShaderStage::CS, (UINT)i);
        }

        ConstantBuffer* pCB = renderer::constantBuffers[(UINT)eCBType::Material];
        pCB->SetData(&mCB);
        pCB->Bind(eShaderStage::VS);
        pCB->Bind(eShaderStage::GS);
        pCB->Bind(eShaderStage::PS);

        mShader->Binds();
    }

    void Material::Clear()
    {
        for (size_t i = 0; i < (UINT)eTextureSlot::End; i++)
        {
            if (mTexture[i] == nullptr)
                continue;

            mTexture[i]->Clear();
        }
    }
}