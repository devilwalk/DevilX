#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSDirectX
		{
			namespace NSVersion11
			{
				class IGADeviceContextImp
					:public TBaseObject<IGADeviceContextImp>
					,public IGADeviceContext
					,public IGADeviceContextFeature_SeparateVAO
					,public IGADeviceContextFeature_ComputeShader
					,public IGADeviceContextFeature_SeparateProgram
					,public IGADeviceContextFeature_IndirectDraw
				{
				protected:
					CComPtr<ID3D11DeviceContext> mInternal;
					std::array<VoidPtr,256> mPointerCache;
				public:
					IGADeviceContextImp(ID3D11Device * device,Bool deferred);
					~IGADeviceContextImp();

					ID3D11DeviceContext * getInternal()const
					{
						return mInternal;
					}

					// 通过 IGADeviceContext 继承
					virtual Void clear(IGADepthStencilView * view,UInt32 flags,Float depth,UInt8 stencil) override;
					virtual Void clear(IGARenderTargetView * view,const Float colourRGBA[4]) override;
					virtual Void clear(IGAUnorderedAccessView * view,const Float value[4]) override;
					virtual Void clear(IGAUnorderedAccessView * view,const UInt32 value[4]) override;
					virtual Void setRenderTargets(UInt32 numRenderTarget,IGARenderTargetView * const * renderTargetViews,IGADepthStencilView * depthStencilView) override;
					virtual Void setInputLayout(IGAInputLayout * layout) override;
					virtual Void setVertexBuffer(UInt32 startSlot,UInt32 numBuffers,IGAVertexBuffer * const * buffers,const UInt32 * strides,const UInt32 * offsets=nullptr) override;
					virtual Void setIndexBuffer(IGAIndexBuffer * buffer,IGAEnum::EIndexBufferFormat format,UInt32 offset=0) override;
					virtual Void setProgram(IGAProgram * program,IGAProgramParameter * parameter) override;
					virtual Void setPrimitiveTopology(IGAEnum::EPrimitiveTopology primitiveTopology) override;
					virtual Void setRasterizerState(IGARasterizerState * state) override;
					virtual Void setDepthStencilState(IGADepthStencilState * state,UInt32 stencilRef) override;
					virtual Void setBlendState(IGABlendState * state,const Float factor[4],UInt32 samplerMask) override;
					virtual Void setScissorRects(UInt32 numRects,const CRect * rects) override;
					virtual Void setViewports(UInt32 numViewports,const IGAStruct::SViewport * viewports) override;
					virtual Void draw(UInt32 vertexCountPerInstance,UInt32 startVertexLocation,UInt32 instanceCount,UInt32 startInstanceLocation) override;
					virtual Void drawIndexed(UInt32 indexCountPerInstance,UInt32 startIndexLocation,Int32 baseVertexLocation,UInt32 instanceCount,UInt32 startInstanceLocation) override;

					// 通过 IGADeviceContext1 继承
					virtual Void setVertexShader(IGAVertexShader* shader,IGAShaderParameter* parameter) override;
					virtual Void setPixelShader(IGAPixelShader* shader,IGAShaderParameter* parameter) override;
					virtual Void setGeometryShader(IGAGeometryShader* shader,IGAShaderParameter* parameter) override;
					virtual Void setHullShader(IGAHullShader* shader,IGAShaderParameter* parameter) override;
					virtual Void setDomainShader(IGADomainShader* shader,IGAShaderParameter* parameter) override;
					virtual Void dispatch(IGAComputeShader* shader,IGAShaderParameter* parameter,UInt32 threadGroupCountX,UInt32 threadGroupCountY,UInt32 threadGroupCountZ) override;

					// 通过 IGADeviceContext 继承
					virtual Void update(IGAHighLevelBuffer* buffer,ConstVoidPtr data,UInt32 updateOffsetInBytes,UInt32 updateSizeInBytes) override;

					// 通过 IGADeviceContext 继承
					virtual Void setVertexArrayObject(IGAVertexArrayObject* vao) override;

					// 通过 IGADeviceContext 继承
					virtual IGADeviceContextFeature_SeparateProgram* queryFeature_SeparateProgram() const override;
					virtual IGADeviceContextFeature_SeparateVAO* queryFeature_SeparateVAO() const override;
					virtual IGADeviceContextFeature_MultiDraw* queryFeature_MultiDraw() const override;
					virtual IGADeviceContextFeature_ComputeShader* queryFeature_ComputeShader() const override;
					virtual IGADeviceContextFeature_IndirectDraw* queryFeature_IndirectDraw() const override;

					// 通过 IGADeviceContextFeature_IndirectDraw 继承
					virtual Void drawIndirect(UInt32 vertexCountPerInstance,UInt32 startVertexLocation=0,UInt32 instanceCount=1,UInt32 startInstanceLocation=0) override;
					virtual Void drawIndexedIndirect(UInt32 indexCountPerInstance,UInt32 startIndexLocation=0,Int32 baseVertexLocation=0,UInt32 instanceCount=1,UInt32 startInstanceLocation=0) override;
				};
			}
		}
	}
}