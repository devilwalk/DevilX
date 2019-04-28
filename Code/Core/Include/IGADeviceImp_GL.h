#pragma once
#include "IGAResourceImp_GL.h"
#include "IGAViewImp_GL.h"
#include "GAEnvironment_GL.h"
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
				const IGAEnum::EDeviceVersion mVersion;
				CGAEnvironment* mEnvironment;

				TResourcePtrUnorderedSet(CGAObject) mCommonObjects;
				TResourcePtrVector(IGAInputLayoutImp) mInputLayouts;
				TResourcePtrVector(IGARasterizerStateImp) mRasterizerStates;
				TResourcePtrVector(IGADepthStencilStateImp) mDepthStencilStates;
				TResourcePtrVector(IGABlendStateImp) mBlendStates;
				TResourcePtrVector(IGASamplerStateImp) mSamplerStates;
				TResourcePtrVector(IGARenderTargetViewImp) mRenderTargetViews;
				TResourcePtrVector(IGADepthStencilViewImp) mDepthStencilViews;
			public:
				IGADeviceImp(IGAEnum::EDeviceVersion version);
				~IGADeviceImp();

				Void setEnvironment(CGAEnvironment* env);
				CGAEnvironment* getEnvironment()const
				{
					return mEnvironment;
				}

				// 通过 IGADevice 继承
				virtual IGAEnum::EDeviceVersion getVersion() const override;
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

				// 通过 IGADeviceContext 继承 
				virtual Void clear(IGADepthStencilView* view,UInt32 flags,Float depth,UInt8 stencil) override;
				virtual Void clear(IGARenderTargetView* view,const Float colourRGBA[4]) override;
				virtual Void clear(IGAUnorderedAccessView* view,const Float value[4]) override;
				virtual Void clear(IGAUnorderedAccessView* view,const UInt32 value[4]) override;
				virtual Void setRenderTargets(UInt32 numRenderTarget,IGARenderTargetView* const* renderTargetViews,IGADepthStencilView* depthStencilView,UInt32 uavStartSlot=0,UInt32 numUAV=0,IGAUnorderedAccessView* const* unorderedAccessViews=nullptr,const UInt32* uavInitialCounts=nullptr) override;
				virtual Void setInputLayout(IGAInputLayout* layout) override;
				virtual Void setVertexBuffer(UInt32 startSlot,UInt32 numBuffers,IGAVertexBuffer* const* buffers,const UInt32* strides,const UInt32* offsets=nullptr) override;
				virtual Void setIndexBuffer(IGAIndexBuffer* buffer,IGAEnum::EGIFormat format,UInt32 offset=0) override;
				virtual Void setProgram(IGAProgram* program,IGAProgramParameter* parameter) override;
				virtual Void setPrimitiveTopology(IGAEnum::EPrimitiveTopology primitiveTopology) override;
				virtual Void setRasterizerState(IGARasterizerState* state) override;
				virtual Void setDepthStencilState(IGADepthStencilState* state,UInt32 stencilRef) override;
				virtual Void setBlendState(IGABlendState* state,const Float factor[4],UInt32 samplerMask=-1) override;
				virtual Void setScissorRects(UInt32 numRects,const CRect* rects) override;
				virtual Void setViewports(UInt32 numViewports,const IGAStruct::SViewport* viewports) override;
				virtual Void draw(UInt32 vertexCountPerInstance,UInt32 startVertexLocation,UInt32 instanceCount=1,UInt32 startInstanceLocation=0) override;
				virtual Void draw(UInt32 indexCountPerInstance,UInt32 startIndexLocation,Int32 baseVertexLocation,UInt32 instanceCount=1,UInt32 startInstanceLocation=0) override;
			protected:
				IGARenderTargetViewImp* _createRenderTargetView(IGATextureImp* texture,UInt32 mipLevel,UInt32 arrayIndex);
				IGADepthStencilViewImp* _createDepthStencilView(IGATextureImp* texture,UInt32 mipLevel,UInt32 arrayIndex);
			};
		}
	}
}