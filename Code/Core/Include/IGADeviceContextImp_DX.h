#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSDirectX
		{
			namespace NSVersion11
			{
				class IGADeviceImp;
				class IGADeviceContextImp
					:public TBaseObject<IGADeviceContextImp>
					,public IGADeviceContext
				{
				protected:
					CComPtr<ID3D11DeviceContext> mInternal;
					std::array<VoidPtr,256> mPointerCache;
				public:
					IGADeviceContextImp(IGADeviceImp * device,Bool deferred);
					~IGADeviceContextImp();

					ID3D11DeviceContext * getInternal()const
					{
						return mInternal;
					}

					// Í¨¹ý IGADeviceContext ¼Ì³Ð
					virtual Void clear(IGADepthStencilView * view,IGAEnum::EClearFlag flags,Float depth,UInt8 stencil) override;
					virtual Void clear(IGARenderTargetView * view,const Float colourRGBA[4]) override;
					virtual Void clear(IGAUnorderedAccessView * view,const Float value[4]) override;
					virtual Void clear(IGAUnorderedAccessView * view,const UInt32 value[4]) override;
					virtual Void setRenderTargets(UInt32 numRenderTarget,IGARenderTargetView * const * renderTargetViews,IGADepthStencilView * depthStencilView,UInt32 uavStartSlot=0,UInt32 numUAV=0,IGAUnorderedAccessView * const * unorderedAccessViews=nullptr,const UInt32 * uavInitialCounts=nullptr) override;
					virtual Void setInputLayout(IGAInputLayout * layout) override;
					virtual Void setVertexBuffer(UInt32 startSlot,UInt32 numBuffers,IGAVertexBuffer * const * buffers,const UInt32 * strides,const UInt32 * offsets=nullptr) override;
					virtual Void setIndexBuffer(IGAIndexBuffer * buffer,IGAEnum::EGIFormat format,UInt32 offset=0) override;
					virtual Void setShader(IGAVertexShader * shader) override;
					virtual Void setShader(IGAPixelShader * shader) override;
					virtual Void setShader(IGAGeometryShader * shader) override;
					virtual Void setShader(IGAHullShader * shader) override;
					virtual Void setShader(IGADomainShader * shader) override;
					virtual Void setShader(IGAComputeShader * shader) override;
					virtual Void setShaderConstantBuffers(IGAEnum::EShaderType shaderType,UInt32 startSlot,UInt32 numBuffers,IGAConstantBuffer * const * buffers) override;
					virtual Void setShaderSampler(IGAEnum::EShaderType shaderType,UInt32 startSlot,UInt32 numSamplers,IGASamplerState * const * samplers) override;
					virtual Void setShaderResources(IGAEnum::EShaderType shaderType,UInt32 startSlot,UInt32 numViews,IGAShaderResourceView * const * views) override;
					virtual Void setPrimitiveTopology(IGAEnum::EPrimitiveTopology primitiveTopology) override;
					virtual Void setRasterizerState(IGARasterizerState * state) override;
					virtual Void setDepthStencilState(IGADepthStencilState * state,UInt32 stencilRef) override;
					virtual Void setBlendState(IGABlendState * state,const Float factor[4],UInt32 samplerMask) override;
					virtual Void setScissorRects(UInt32 numRects,const CRect * rects) override;
					virtual Void setViewports(UInt32 numViewports,const IGAStruct::SViewport * viewports) override;
					virtual Void draw(UInt32 vertexCountPerInstance,UInt32 startVertexLocation,UInt32 instanceCount,UInt32 startInstanceLocation) override;
					virtual Void draw(UInt32 indexCountPerInstance,UInt32 startIndexLocation,Int32 baseVertexLocation,UInt32 instanceCount,UInt32 startInstanceLocation) override;
				};
			}
		}
	}
}