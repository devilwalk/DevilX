#pragma once
#include "IGAResourceImp_GL.h"
#include "IGAViewImp_GL.h"
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSOpenGL
		{
			class IGADeviceImp
				:public TBaseObject<IGADeviceImp>
				,public IGADevice
				,public IGADeviceContext
			{
			protected:
				HGLRC mContext;
				GLuint mFrameBufferObject;

				TResourcePtrUnorderedSet(CGAObject) mCommonObjects;
				TResourcePtrVector(IGAInputLayoutImp) mInputLayouts;
				TResourcePtrVector(IGARasterizerStateImp) mRasterizerStates;
				TResourcePtrVector(IGADepthStencilStateImp) mDepthStencilStates;
				TResourcePtrVector(IGABlendStateImp) mBlendStates;
				TResourcePtrVector(IGASamplerStateImp) mSamplerStates;
				TResourcePtrVector(IGARenderTargetViewImp) mRenderTargetViews;
				TResourcePtrVector(IGADepthStencilViewImp) mDepthStencilViews;
			public:
				IGADeviceImp();
				~IGADeviceImp();

				// 通过 IGADevice 继承
				virtual IGADeviceContext * getImmediateContext() const override;
				virtual IGADeviceContext * createDeferredContext() override;

				// 通过 IGADevice 继承
				virtual IGAVertexBuffer* createVertexBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage=IGAEnum::EUsage_DEFAULT,UInt32 bindFlags=0,ConstVoidPtr initialData=nullptr) override;
				virtual IGAIndexBuffer* createIndexBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage=IGAEnum::EUsage_DEFAULT,UInt32 bindFlags=0,ConstVoidPtr initialData=nullptr) override;
				virtual IGAConstantBuffer* createConstantBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage=IGAEnum::EUsage_DEFAULT,UInt32 bindFlags=0,ConstVoidPtr initialData=nullptr) override;
				virtual IGAUnorderedAccessBuffer* createUnorderedAccessBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage=IGAEnum::EUsage_DEFAULT,UInt32 bindFlags=0,ConstVoidPtr initialData=nullptr) override;
				virtual IGATexture1D* createTexture1D(UInt32 length,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount=0,UInt32 arrayCount=1,const IGAStruct::SSubResourceData* initialData=nullptr) override;
				virtual IGATexture2D* createTexture2D(UInt32 width,UInt32 height,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount=0,UInt32 arrayCount=1,const IGAStruct::SSubResourceData* initialData=nullptr) override;
				virtual IGATexture3D* createTexture3D(UInt32 width,UInt32 height,UInt32 depth,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount=0,const IGAStruct::SSubResourceData* initialData=nullptr) override;
				virtual IGATexture2D* createTextureCube(UInt32 width,UInt32 height,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount=0,UInt32 arrayCount=1,const IGAStruct::SSubResourceData* initialData=nullptr) override;
				virtual IGARenderTargetView* createRenderTargetView(IGATexture1D* resource,UInt32 mipSlice=0,UInt32 firstArraySlice=0) override;
				virtual IGARenderTargetView* createRenderTargetView(IGATexture2D* resource,UInt32 mipSlice=0,UInt32 firstArraySlice=0) override;
				virtual IGARenderTargetView* createRenderTargetView(IGATexture3D* resource,UInt32 mipSlice,UInt32 firstDepthSlice) override;
				virtual IGADepthStencilView* createDepthStencilView(IGATexture1D* resource,UInt32 mipSlice=0,UInt32 firstArraySlice=0) override;
				virtual IGADepthStencilView* createDepthStencilView(IGATexture2D* resource,UInt32 mipSlice=0,UInt32 firstArraySlice=0) override;
				virtual IGAShaderResourceView* createShaderResourceView(IGATexture1D* resource,UInt32 mostDetailedMip=0,UInt32 numMipLevels=-1,UInt32 firstArraySlice=0,UInt32 arrayCount=0) override;
				virtual IGAShaderResourceView* createShaderResourceView(IGATexture2D* resource,UInt32 mostDetailedMip=0,UInt32 numMipLevels=-1,UInt32 firstArraySlice=0,UInt32 arrayCount=0) override;
				virtual IGAShaderResourceView* createShaderResourceView(IGATexture3D* resource,UInt32 mostDetailedMip=0,UInt32 numMipLevels=-1) override;
				virtual IGAUnorderedAccessView* createUnorderedAccessView(IGATexture1D* resource,UInt32 mipSlice=0,UInt32 firstArraySlice=0,UInt32 arrayCount=1) override;
				virtual IGAUnorderedAccessView* createUnorderedAccessView(IGATexture2D* resource,UInt32 mipSlice=0,UInt32 firstArraySlice=0,UInt32 arrayCount=1) override;
				virtual IGAUnorderedAccessView* createUnorderedAccessView(IGATexture3D* resource,UInt32 mipSlice,UInt32 firstDepthSlice,UInt32 depthCount) override;
				virtual IGAInputLayout* createInputLayout(const TVector<IGAStruct::SInputElementDesc>& inputElements) override;
				virtual IGAVertexShader* createVertexShader(const std::string& code) override;
				virtual IGAPixelShader* createPixelShader(const std::string& code) override;
				virtual IGAGeometryShader* createGeometryShader(const std::string& code) override;
				virtual IGAHullShader* createHullShader(const std::string& code) override;
				virtual IGADomainShader* createDomainShader(const std::string& code) override;
				virtual IGAComputeShader* createComputeShader(const std::string& code) override;
				virtual IGABlendState* createBlendState(const IGAStruct::SBlendDesc& desc) override;
				virtual IGARasterizerState* createRasterizerState(const IGAStruct::SRasterizerDesc& desc) override;
				virtual IGADepthStencilState* createDepthStencilState(const IGAStruct::SDepthStencilDesc& desc) override;
				virtual IGASamplerState* createSamplerState(const IGAStruct::SSamplerDesc& desc) override;
				virtual IGAProgram* createProgram(IGAVertexShader* vertexShader,IGAPixelShader* pixelShader,IGAGeometryShader* geometryShader=nullptr,IGAHullShader* hullShader=nullptr,IGADomainShader* domainShader=nullptr) override;
				virtual IGAProgram* createProgram(IGAComputeShader* computeShader) override;
				virtual IGAProgramReflection* createReflection(IGAProgram* program) override;
				virtual Void destroyReflection(IGAProgramReflection* reflection) override;
				virtual IGAProgramParameter* createProgramParameter() override;
				virtual Void destroyProgramParameter(IGAProgramParameter* parameter) override;
			};
		}
	}
}