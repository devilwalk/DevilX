#pragma once
#include "IGADeviceContextImp_DX.h"
#include "IGAResourceImp_DX11.h"
#include "IGAShaderReflectionImp_DX.h"
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
					TResourcePtrVector(IGAResourceImp) mCommonResources;
					TResourcePtrVector(IGAInputLayoutImp) mInputLayouts;
					TResourcePtrVector(IGARasterizerStateImp) mRasterizerStates;
					TResourcePtrVector(IGADepthStencilStateImp) mDepthStencilStates;
					TResourcePtrVector(IGABlendStateImp) mBlendStates;
					TResourcePtrVector(IGASamplerStateImp) mSamplerStates;
					TResourcePtrUnorderedSet(IGAShaderReflectionImp) mShaderReflections;
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
					virtual IGAVertexBuffer * createVertexBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage=IGAEnum::EUsage_DEFAULT,UInt32 bindFlags=0,ConstVoidPtr initialData=nullptr) override;
					virtual IGAIndexBuffer * createIndexBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage=IGAEnum::EUsage_DEFAULT,UInt32 bindFlags=0,ConstVoidPtr initialData=nullptr) override;
					virtual IGAConstantBuffer * createConstantBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage=IGAEnum::EUsage_DEFAULT,UInt32 bindFlags=0,ConstVoidPtr initialData=nullptr) override;
					virtual IGAUnorderedAccessBuffer * createUnorderedAccessBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage=IGAEnum::EUsage_DEFAULT,UInt32 bindFlags=0,ConstVoidPtr initialData=nullptr) override;
					virtual IGATexture1D * createTexture1D(UInt32 length,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount=0,UInt32 arrayCount=1,const IGAStruct::SSubResourceData * initialData=nullptr) override;
					virtual IGATexture2D * createTexture2D(UInt32 width,UInt32 height,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount=0,UInt32 arrayCount=1,const IGAStruct::SSubResourceData * initialData=nullptr) override;
					virtual IGATexture3D * createTexture3D(UInt32 width,UInt32 height,UInt32 depth,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount=0,const IGAStruct::SSubResourceData * initialData=nullptr) override;
					virtual IGATexture2D * createTextureCube(UInt32 width,UInt32 height,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount=0,UInt32 arrayCount=1,const IGAStruct::SSubResourceData * initialData=nullptr) override;
					virtual IGAShaderResourceView * createShaderResourceView(IGAResource * resource,const IGAStruct::SShaderResourceViewDesc * desc=nullptr) override;
					virtual IGAInputLayout * createInputLayout(const TVector<IGAStruct::SInputElementDesc> & inputElements) override;
					virtual IGABlendState * createBlendState(const IGAStruct::SBlendDesc & desc) override;
					virtual IGARasterizerState * createRasterizerState(const IGAStruct::SRasterizerDesc & desc) override;
					virtual IGADepthStencilState * createDepthStencilState(const IGAStruct::SDepthStencilDesc & desc) override;
					virtual IGASamplerState * createSamplerState(const IGAStruct::SSamplerDesc & desc) override;
					virtual IGAVertexShader * createVertexShader(const std::string & code) override;
					virtual IGAPixelShader * createPixelShader(const std::string & code) override;
					virtual IGAGeometryShader * createGeometryShader(const std::string & code) override;
					virtual IGAHullShader * createHullShader(const std::string & code) override;
					virtual IGADomainShader * createDomainShader(const std::string & code) override;
					virtual IGAComputeShader * createComputeShader(const std::string & code) override;
					virtual IGAProgram * createProgram(IGAVertexShader * vertexShader,IGAPixelShader * pixelShader,IGAGeometryShader * geometryShader=nullptr,IGAHullShader * hullShader=nullptr,IGADomainShader * domainShader=nullptr) override;
					virtual IGAProgram * createProgram(IGAComputeShader * computeShader) override;
					virtual IGAShaderReflection * createShaderReflection(IGAProgram * program) override;
					virtual Void destroyShaderReflection(IGAShaderReflection * reflection) override;
					virtual IGAProgramParameter * createProgramParameter() override;
					virtual Void destroyProgramParameter(IGAProgramParameter * parameter) override;
				protected:
				};
			}
		}
	}
}