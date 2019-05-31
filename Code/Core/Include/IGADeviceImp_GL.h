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
				:public IGAHighLevelDevice
				,public IGADevice
				,public IGAHighLevelDeviceFeature_SeparateProgram
				,public IGAHighLevelDeviceFeature_SeparateVAO
				,public IGAHighLevelDeviceFeature_ComputeShader
			{
			public:
				IGADeviceImp(){ }
				virtual ~IGADeviceImp(){ }

				virtual IGADevice* queryInterface_IGADevice() const override
				{
					return const_cast<IGADeviceImp*>(this);
				}
				virtual IGAHighLevelDeviceFeature_SeparateProgram* queryFeature_SeparateProgram() const override
				{
					return const_cast<IGADeviceImp*>(this);
				}
				virtual IGAHighLevelDeviceFeature_SeparateVAO* queryFeature_SeparateVAO() const override
				{
					return const_cast<IGADeviceImp*>(this);
				}
				virtual IGAHighLevelDeviceFeature_ComputeShader* queryFeature_ComputeShader() const override
				{
					return const_cast<IGADeviceImp*>(this);
				}
			};
			class IGADeviceContextImp
				:public IGADeviceContext
				,public IGADeviceContextFeature_ComputeShader
				,public IGADeviceContextFeature_SeparateVAO
				,public IGADeviceContextFeature_SeparateProgram
				,public IGADeviceContextFeature_MultiDraw
				,public IGADeviceContextFeature_IndirectDraw
			{
			public:
				IGADeviceContextImp()
				{
				}
				virtual ~IGADeviceContextImp()
				{
				}

				virtual IGADeviceContextFeature_SeparateProgram* queryFeature_SeparateProgram() const override
				{
					return const_cast<IGADeviceContextImp*>(this);
				}
				virtual IGADeviceContextFeature_SeparateVAO* queryFeature_SeparateVAO() const override
				{
					return const_cast<IGADeviceContextImp*>(this);
				}
				virtual IGADeviceContextFeature_ComputeShader* queryFeature_ComputeShader() const override
				{
					return const_cast<IGADeviceContextImp*>(this);
				}
				virtual IGADeviceContextFeature_MultiDraw* queryFeature_MultiDraw() const override
				{
					return const_cast<IGADeviceContextImp*>(this);
				}
			};
			class CGADeviceImp
				:public TBaseObject<CGADeviceImp>
				,public IGADeviceImp
				,public IGADeviceContextImp
			{
			protected:
				const IGAEnum::EHighLevelDeviceVersion mVersion;
				GLenum mDrawMode;
				GLenum mIndexType;
				UInt32 mIndexOffset;
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
				CGADeviceImp(IGAEnum::EHighLevelDeviceVersion version);
				~CGADeviceImp();

				Void setEnvironment(CGAEnvironment* env);
				CGAEnvironment* getEnvironment() const
				{
					return mEnvironment;
				}

				// 通过 IGADevice 继承
				virtual IGAEnum::EHighLevelDeviceVersion getVersion() const override;
				virtual IGADeviceContext* getImmediateContext() const override;
				virtual IGADeviceContext* createDeferredContext() override;

				// 通过 IGADevice 继承
				virtual IGAVertexBuffer* createVertexBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage=IGAEnum::EUsage_DEFAULT,UInt32 bindFlags=0,ConstVoidPtr initialData=nullptr) override;
				virtual IGAIndexBuffer* createIndexBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage=IGAEnum::EUsage_DEFAULT,UInt32 bindFlags=0,ConstVoidPtr initialData=nullptr) override;
				virtual IGAConstantBuffer* createConstantBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage=IGAEnum::EUsage_DEFAULT,UInt32 bindFlags=0,ConstVoidPtr initialData=nullptr) override;
				virtual IGAShaderResourceBuffer* createShaderResourceBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags=0,UInt32 shaderResourceBufferFlags=0,UInt32 structureByteStride=0,IGAEnum::EUsage usage=IGAEnum::EUsage_DEFAULT,UInt32 bindFlags=0,ConstVoidPtr initialData=nullptr) override;
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
				virtual IGATextureView* createShaderResourceView(IGATexture1D* resource,UInt32 mostDetailedMip=0,UInt32 numMipLevels=-1,UInt32 firstArraySlice=0,UInt32 arrayCount=0) override;
				virtual IGATextureView* createShaderResourceView(IGATexture2D* resource,UInt32 mostDetailedMip=0,UInt32 numMipLevels=-1,UInt32 firstArraySlice=0,UInt32 arrayCount=0) override;
				virtual IGATextureView* createShaderResourceView(IGATexture3D* resource,UInt32 mostDetailedMip=0,UInt32 numMipLevels=-1) override;
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
				virtual IGAProgramReflection* createReflection(IGAProgram* program) override;
				virtual Void destroyReflection(IGAProgramReflection* reflection) override;
				virtual IGAProgramParameter* createProgramParameter() override;
				virtual Void destroyProgramParameter(IGAProgramParameter* parameter) override;
				virtual IGAShaderParameter* createShaderParameter() override;
				virtual IGAComputeShaderParameter* createComputeShaderParameter() override;
				virtual Void destroyShaderParameter(IGAShaderParameter* parameter) override;
				virtual IGAShaderReflection* createReflection(IGAShader* shader) override;
				virtual Void destroyReflection(IGAShaderReflection* reflection) override;
				virtual IGAShaderResourceBufferView* createShaderResourceView(IGAShaderResourceBuffer* resource,IGAEnum::EGIFormat format,UInt32 elementOffset=0,UInt32 numElements=-1) override;
				virtual IGAVertexArrayObject* createVertexArrayObject(const TVector<IGAStruct::SVAOElementDesc>& inputElements) override;

				// 通过 IGADeviceContext 继承 
				virtual Void clear(IGADepthStencilView* view,UInt32 flags,Float depth,UInt8 stencil) override;
				virtual Void clear(IGARenderTargetView* view,const Float colourRGBA[4]) override;
				virtual Void clear(IGAUnorderedAccessView* view,const Float value[4]) override;
				virtual Void clear(IGAUnorderedAccessView* view,const UInt32 value[4]) override;
				virtual Void setRenderTargets(UInt32 numRenderTarget,IGARenderTargetView* const* renderTargetViews,IGADepthStencilView* depthStencilView) override;
				virtual Void setInputLayout(IGAInputLayout* layout) override;
				virtual Void setVertexBuffer(UInt32 startSlot,UInt32 numBuffers,IGAVertexBuffer* const* buffers,const UInt32* strides,const UInt32* offsets=nullptr) override;
				virtual Void setProgram(IGAProgram* program,IGAProgramParameter* parameter) override;
				virtual Void setRasterizerState(IGARasterizerState* state) override;
				virtual Void setDepthStencilState(IGADepthStencilState* state,UInt32 stencilRef) override;
				virtual Void setBlendState(IGABlendState* state,const Float factor[4],UInt32 samplerMask=-1) override;
				virtual Void setScissorRects(UInt32 numRects,const CRect* rects) override;
				virtual Void setViewports(UInt32 numViewports,const IGAStruct::SViewport* viewports) override;
				virtual Void setVertexShader(IGAVertexShader* shader,IGAShaderParameter* parameter) override;
				virtual Void setPixelShader(IGAPixelShader* shader,IGAShaderParameter* parameter) override;
				virtual Void setGeometryShader(IGAGeometryShader* shader,IGAShaderParameter* parameter) override;
				virtual Void setHullShader(IGAHullShader* shader,IGAShaderParameter* parameter) override;
				virtual Void setDomainShader(IGADomainShader* shader,IGAShaderParameter* parameter) override;
				virtual Void dispatch(IGAComputeShader* shader,IGAShaderParameter* parameter,UInt32 threadGroupCountX,UInt32 threadGroupCountY,UInt32 threadGroupCountZ) override;
				virtual Void update(IGAHighLevelBuffer* buffer,ConstVoidPtr data,UInt32 updateOffsetInBytes=0,UInt32 updateSizeInBytes=0) override;
				virtual Void draw(const TVector<IGAStruct::SDrawParameter_GL>& parameters) override;
				virtual Void draw(const TVector<IGAStruct::SDrawIndexedParameter_GL>& parameters) override;
				virtual Void setIndexBuffer(IGAIndexBuffer* buffer,IGAEnum::EIndexBufferFormat format,UInt32 offset=0) override;
				virtual Void setPrimitiveTopology(IGAEnum::EPrimitiveTopology primitiveTopology) override;
				virtual Void draw(UInt32 vertexCountPerInstance,UInt32 startVertexLocation,UInt32 instanceCount=1,UInt32 startInstanceLocation=0) override;
				virtual Void drawIndexed(UInt32 indexCountPerInstance,UInt32 startIndexLocation,Int32 baseVertexLocation,UInt32 instanceCount=1,UInt32 startInstanceLocation=0) override;
				virtual Void setVertexArrayObject(IGAVertexArrayObject* vao) override;
			protected:
				IGARenderTargetViewImp* _createRenderTargetView(IGATextureImp* texture,UInt32 mipLevel,UInt32 arrayIndex);
				IGADepthStencilViewImp* _createDepthStencilView(IGATextureImp* texture,UInt32 mipLevel,UInt32 arrayIndex);
			};
		}
	}
}