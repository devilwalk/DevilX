#pragma once
#include "ICoreGPUEnum.h"
#include "ICoreGPUView.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class IGPUCommandList
		{
		protected:
			virtual ~IGPUCommandList(){ }
		public:
		};
		class IGPUGraphicCommandList
		{
		protected:
			virtual ~IGPUGraphicCommandList()
			{
			}
		public:
			virtual IGPUCommandList * queryInterface_IGPUCommandList()=0;
			virtual Void setPrimitiveTopology(IGPUEnum::EPrimitiveTopology primitiveTopology)=0;
			virtual Void setBlendFactor(const Float factor[4])=0;
			virtual Void setStencilRef(UInt32 stencilRef)=0;
			virtual Void setScissorRects(UInt32 numRects,const CRect * rects)=0;
			virtual Void setViewports(UInt32 numViewports,const SViewport * viewports)=0;
			virtual Void draw(UInt32 vertexCountPerInstance,UInt32 instanceCount,UInt32 startVertexLocation,UInt32 startInstanceLocation)=0;
			virtual Void draw(UInt32 indexCountPerInstance,UInt32 instanceCount,UInt32 startIndexLocation,Int32 baseVertexLocation,UInt32 startInstanceLocation)=0;
			virtual Void execute(IGPUGraphicCommandList * bundle)=0;
			virtual Void finish()=0;
		};
		class IGPUGraphicCommandList11
		{
		protected:
			virtual ~IGPUGraphicCommandList11()
			{
			}
		public:
			virtual IGPUGraphicCommandList * queryInterface_IGPUGraphicCommandList()=0;
			virtual Void clear(IGPUDepthStencilView * view,IGPUEnum::EClearFlag flags,Float depth,UInt8 stencil)=0;
			virtual Void clear(IGPURenderTargetView * view,const Float colourRGBA[4])=0;
			virtual Void clear(IGPUUnorderedAccessView * view,const Float value[4])=0;
			virtual Void clear(IGPUUnorderedAccessView * view,const UInt32 value[4])=0;
			virtual Void clearState()=0;
			virtual Void setRenderTarget(UInt32 numRenderTarget,IGPURenderTargetView * const * renderTargetViews,IGPUDepthStencilView * depthStencilView)=0;
			virtual Void setInputLayout(IGPUInputLayout * layout)=0;
			virtual Void setVertexBuffer(UInt32 startSlot,UInt32 numViews,IGPUBuffer * const * buffers,const UInt32 * strides,const UInt32 * offsets=nullptr)=0;
			virtual Void setIndexBuffer(IGPUBuffer * buffer,IGPUEnum::EGIFormat format,UInt32 offset=0)=0;
			virtual Void setVertexShader(IGPUShader * shader)=0;
			virtual Void setVertexShaderConstantBuffers(UInt32 startSlot,UInt32 numBuffers,IGPUBuffer * const * buffers)=0;
			virtual Void setVertexShaderSampler(UInt32 startSlot,UInt32 numSamplers,IGPUSampler * const * samplers)=0;
			virtual Void setVertexShaderResources(UInt32 startSlot,UInt32 numViews,IGPUShaderResourceView * const * views)=0;
			virtual Void setGeometryShader(IGPUShader * shader)=0;
			virtual Void setGeometryShaderConstantBuffers(UInt32 startSlot,UInt32 numBuffers,IGPUBuffer * const * buffers)=0;
			virtual Void setGeometryShaderSampler(UInt32 startSlot,UInt32 numSamplers,IGPUSampler * const * samplers)=0;
			virtual Void setPixelShader(IGPUShader * shader)=0;
			virtual Void setPixelShaderConstantBuffers(UInt32 startSlot,UInt32 numBuffers,IGPUBuffer * const * buffers)=0;
			virtual Void setPixelShaderSampler(UInt32 startSlot,UInt32 numSamplers,IGPUSampler * const * samplers)=0;
			virtual Void setPixelShaderResources(UInt32 startSlot,UInt32 numViews,IGPUShaderResourceView * const * views)=0;
		};
	}
}