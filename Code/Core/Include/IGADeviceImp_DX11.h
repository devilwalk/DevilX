#pragma once
#include "IGADeviceContextImp_DX.h"
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSDirectX
		{
			namespace NSVersion11
			{
				class IGADeviceImp
					:public TBaseObject<IGADeviceImp>
					,public IGADevice
				{
				protected:
					D3D_FEATURE_LEVEL mFeatureLevel;
					CComPtr<ID3D11Device> mInternal;
					TResourcePtrVector(IGADeviceContextImp) mContexts;

					TRefResourcePtrUnorderedMap(CD3D11_RASTERIZER_DESC,IGARasterizerStateImp) mRasterizerStates;
					TRefResourcePtrUnorderedMap(CD3D11_DEPTH_STENCIL_DESC,IGADepthStencilStateImp) mDepthStencilStates;
					TRefResourcePtrUnorderedMap(CD3D11_BLEND_DESC,IGABlendStateImp) mBlendStates;
					TRefResourcePtrUnorderedMap(CD3D11_SAMPLER_DESC,IGASamplerStateImp) mSamplerStates;
				public:
					IGADeviceImp();
					~IGADeviceImp();

					ID3D11Device * getInternal()const
					{
						return mInternal;
					}

					// Í¨¹ý IGADevice ¼Ì³Ð
					virtual IGADeviceContext * getImmediateContext() const override;
					virtual IGADeviceContext * createDeferredContext() override;
					virtual IGAVertexBuffer * createVertexBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage=IGAEnum::EUsage_DEFAULT,UInt32 bindFlags=0,const IGAStruct::SSubResourceData * initialData=nullptr) override;
					virtual IGAIndexBuffer * createIndexBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage=IGAEnum::EUsage_DEFAULT,UInt32 bindFlags=0,const IGAStruct::SSubResourceData * initialData=nullptr) override;
					virtual IGAConstantBuffer * createConstantBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage=IGAEnum::EUsage_DEFAULT,UInt32 bindFlags=0,const IGAStruct::SSubResourceData * initialData=nullptr) override;
					virtual IGAUnorderedAccessBuffer * createUnorderedAccessBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage=IGAEnum::EUsage_DEFAULT,UInt32 bindFlags=0,const IGAStruct::SSubResourceData * initialData=nullptr) override;
					virtual IGATexture1D * createTexture1D(UInt32 length,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount=0,UInt32 arrayCount=1,const IGAStruct::SSubResourceData * initialData=nullptr) override;
					virtual IGATexture2D * createTexture2D(UInt32 width,UInt32 height,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount=0,UInt32 arrayCount=1,const IGAStruct::SSubResourceData * initialData=nullptr) override;
					virtual IGATexture3D * createTexture3D(UInt32 width,UInt32 height,UInt32 depth,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount=0,const IGAStruct::SSubResourceData * initialData=nullptr) override;
					virtual IGATexture2D * createTextureCube(UInt32 width,UInt32 height,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount=0,UInt32 arrayCount=1,const IGAStruct::SSubResourceData * initialData=nullptr) override;
					virtual IGAShaderResourceView * createShaderResourceView(IGAResource * resource,const IGAStruct::SShaderResourceViewDesc * desc=nullptr) override;
					virtual IGAInputLayout * createInputLayout(const IGAStruct::SInputLayoutDesc & desc) override;
					virtual IGABlendState * createBlendState(const IGAStruct::SBlendDesc & desc) override;
					virtual IGARasterizerState * createRasterizerState(const IGAStruct::SRasterizerDesc & desc) override;
					virtual IGADepthStencilState * createDepthStencilState(const IGAStruct::SDepthStencilDesc & desc) override;
					virtual IGASamplerState * createSamplerState(const IGAStruct::SSamplerDesc & desc) override;
					virtual IGAVertexShader * createVertexShader(ConstVoidPtr code,SizeT codeSize) override;
					virtual IGAPixelShader * createPixelShader(ConstVoidPtr code,SizeT codeSize) override;
					virtual IGAGeometryShader * createGeometryShader(ConstVoidPtr code,SizeT codeSize) override;
					virtual IGAHullShader * createHullShader(ConstVoidPtr code,SizeT codeSize) override;
					virtual IGADomainShader * createDomainShader(ConstVoidPtr code,SizeT codeSize) override;
					virtual IGAComputeShader * createComputeShader(ConstVoidPtr code,SizeT codeSize) override;
				};
			}
		}
	}
}