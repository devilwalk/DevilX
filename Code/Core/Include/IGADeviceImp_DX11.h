#pragma once
#include "IGADeviceContextImp_DX.h"
#include "IGAResourceImp_DX11.h"
#include "IGAProgramReflectionImp_DX.h"
#include "IGAViewImp_DX.h"
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
					,public IGAHighLevelDevice
					,public IGAHighLevelDeviceFeature_SeparateProgram
					,public IGAHighLevelDeviceFeature_SeparateVAO
					,public IGAHighLevelDeviceFeature_ComputeShader
				{
				protected:
					D3D_FEATURE_LEVEL mFeatureLevel;
					CComPtr<ID3D11Device> mInternal;
					TResourcePtrVector(IGADeviceContextImp) mContexts;
					TResourcePtrUnorderedSet(CGAObject) mCommonObjects;
					TResourcePtrVector(IGAInputLayoutImp) mInputLayouts;
					TResourcePtrVector(IGARasterizerStateImp) mRasterizerStates;
					TResourcePtrVector(IGADepthStencilStateImp) mDepthStencilStates;
					TResourcePtrVector(IGABlendStateImp) mBlendStates;
					TResourcePtrVector(IGASamplerStateImp) mSamplerStates;
					TResourcePtrVector(IGARenderTargetViewImp) mRenderTargetViews;
					TResourcePtrVector(IGADepthStencilViewImp) mDepthStencilViews;
					TResourcePtrVector(IGAShaderResourceViewImp) mShaderResourceViews;
				public:
					IGADeviceImp();
					~IGADeviceImp();

					ID3D11Device * getInternal()const
					{
						return mInternal;
					}
					template<class TID3D11Device>
					TID3D11Device * getInternal()
					{
						TID3D11Device * ret=nullptr;
						mInternal->QueryInterface(&ret);
						return ret;
					}

					// 通过 IGADevice 继承
					virtual IGAEnum::EHighLevelDeviceVersion getVersion() const override;
					virtual IGADeviceContext * getImmediateContext() const override;
					virtual IGADeviceContext * createDeferredContext() override;
					virtual IGAVertexBuffer * createVertexBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage=IGAEnum::EUsage_DEFAULT,UInt32 bindFlags=0,ConstVoidPtr initialData=nullptr) override;
					virtual IGAIndexBuffer * createIndexBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage=IGAEnum::EUsage_DEFAULT,UInt32 bindFlags=0,ConstVoidPtr initialData=nullptr) override;
					virtual IGAConstantBuffer * createConstantBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage=IGAEnum::EUsage_DEFAULT,UInt32 bindFlags=0,ConstVoidPtr initialData=nullptr) override;
					virtual IGAShaderResourceBuffer* createShaderResourceBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags=0,UInt32 shaderResourceBufferFlags=0,UInt32 structureByteStride=0,IGAEnum::EUsage usage=IGAEnum::EUsage_DEFAULT,UInt32 bindFlags=0,ConstVoidPtr initialData=nullptr) override;
					virtual IGAUnorderedAccessBuffer * createUnorderedAccessBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage=IGAEnum::EUsage_DEFAULT,UInt32 bindFlags=0,ConstVoidPtr initialData=nullptr) override;
					virtual IGATexture1D * createTexture1D(UInt32 length,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount=0,UInt32 arrayCount=1,const IGAStruct::SSubResourceData * initialData=nullptr) override;
					virtual IGATexture2D * createTexture2D(UInt32 width,UInt32 height,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount=0,UInt32 arrayCount=1,const IGAStruct::SSubResourceData * initialData=nullptr) override;
					virtual IGATexture3D * createTexture3D(UInt32 width,UInt32 height,UInt32 depth,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount=0,const IGAStruct::SSubResourceData * initialData=nullptr) override;
					virtual IGATexture2D * createTextureCube(UInt32 width,UInt32 height,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount=0,UInt32 arrayCount=1,const IGAStruct::SSubResourceData * initialData=nullptr) override;
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
					virtual IGAProgramReflection * createReflection(IGAProgram * program) override;
					virtual Void destroyReflection(IGAProgramReflection * reflection) override;
					virtual IGAProgramParameter * createProgramParameter() override;
					virtual Void destroyProgramParameter(IGAProgramParameter * parameter) override;
					virtual IGAShaderParameter* createShaderParameter() override;
					virtual IGAComputeShaderParameter* createComputeShaderParameter() override;
					virtual Void destroyShaderParameter(IGAShaderParameter* parameter) override;

					// 通过 IGADevice 继承
					virtual IGARenderTargetView* createRenderTargetView(IGATexture1D* resource,UInt32 mipSlice=0,UInt32 firstArraySlice=0) override;
					virtual IGARenderTargetView* createRenderTargetView(IGATexture2D* resource,UInt32 mipSlice=0,UInt32 firstArraySlice=0) override;
					virtual IGARenderTargetView* createRenderTargetView(IGATexture3D* resource,UInt32 mipSlice,UInt32 firstDepthSlice) override;
					virtual IGADepthStencilView* createDepthStencilView(IGATexture1D* resource,UInt32 mipSlice=0,UInt32 firstArraySlice=0) override;
					virtual IGADepthStencilView* createDepthStencilView(IGATexture2D* resource,UInt32 mipSlice=0,UInt32 firstArraySlice=0) override;
					virtual IGATextureView* createShaderResourceView(IGATexture1D* resource,UInt32 mostDetailedMip=0,UInt32 numMipLevels=-1,UInt32 firstArraySlice=0,UInt32 arrayCount=0) override;
					virtual IGATextureView* createShaderResourceView(IGATexture2D* resource,UInt32 mostDetailedMip=0,UInt32 numMipLevels=-1,UInt32 firstArraySlice=0,UInt32 arrayCount=0) override;
					virtual IGATextureView* createShaderResourceView(IGATexture3D* resource,UInt32 mostDetailedMip=0,UInt32 numMipLevels=-1) override;
					virtual IGAUnorderedAccessView* createUnorderedAccessView(IGATexture1D* resource,UInt32 mipSlice=0,UInt32 firstArraySlice=0,UInt32 arrayCount=0) override;
					virtual IGAUnorderedAccessView* createUnorderedAccessView(IGATexture2D* resource,UInt32 mipSlice=0,UInt32 firstArraySlice=0,UInt32 arrayCount=0) override;
					virtual IGAUnorderedAccessView* createUnorderedAccessView(IGATexture3D* resource,UInt32 mipSlice,UInt32 firstDepthSlice,UInt32 depthCount) override;

					// 通过 IGADevice1 继承
					virtual IGAShaderReflection* createReflection(IGAShader* shader) override;
					virtual Void destroyReflection(IGAShaderReflection* reflection) override;

				protected:
					IGARenderTargetViewImp * _create(ID3D11Resource * resource,const D3D11_RENDER_TARGET_VIEW_DESC * desc);
					IGADepthStencilViewImp * _create(ID3D11Resource * resource,const D3D11_DEPTH_STENCIL_VIEW_DESC * desc);
					IGAShaderResourceViewImp * _create(ID3D11Resource * resource,const D3D11_SHADER_RESOURCE_VIEW_DESC * desc);

					// 通过 IGADevice 继承
					virtual IGAShaderResourceBufferView* createShaderResourceView(IGAShaderResourceBuffer* resource,IGAEnum::EGIFormat format,UInt32 elementOffset,UInt32 numElements) override;

					// 通过 IGADevice 继承
					virtual IGAVertexArrayObject* createVertexArrayObject(const TVector<IGAStruct::SVAOElementDesc>& inputElements) override;

					// 通过 IGADevice 继承
					virtual IGAHighLevelDeviceFeature_SeparateVAO* queryFeature_SeparateVAO() const override;
					virtual IGAHighLevelDeviceFeature_ComputeShader* queryFeature_ComputeShader() const override;
					virtual IGAHighLevelDeviceFeature_SeparateProgram* queryFeature_SeparateProgram() const override;

					// 通过 IGAHighLevelDevice 继承
					virtual IGADevice* queryInterface_IGADevice() const override;
					};
			}
		}
	}
}