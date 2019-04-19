#pragma once
#include "ICoreGAEnum.h"
#include "ICoreGAStruct.h"
#include "ICoreGAView.h"
#include "ICoreGAResource.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class IGADeviceContext
		{
		protected:
			virtual ~IGADeviceContext()
			{
			}
		public:
			virtual Void clear(IGADepthStencilView * view,IGAEnum::EClearFlag flags,Float depth,UInt8 stencil)=0;
			virtual Void clear(IGARenderTargetView * view,const Float colourRGBA[4])=0;
			virtual Void clear(IGAUnorderedAccessView * view,const Float value[4])=0;
			virtual Void clear(IGAUnorderedAccessView * view,const UInt32 value[4])=0;
			virtual Void setRenderTargets(UInt32 numRenderTarget,IGARenderTargetView * const * renderTargetViews,IGADepthStencilView * depthStencilView,UInt32 uavStartSlot=0,UInt32 numUAV=0,IGAUnorderedAccessView *const* unorderedAccessViews=nullptr,const UInt32 * uavInitialCounts=nullptr)=0;
			virtual Void setInputLayout(IGAInputLayout * layout)=0;
			virtual Void setVertexBuffer(UInt32 startSlot,UInt32 numBuffers,IGAVertexBuffer * const * buffers,const UInt32 * strides,const UInt32 * offsets=nullptr)=0;
			virtual Void setIndexBuffer(IGAIndexBuffer * buffer,IGAEnum::EGIFormat format,UInt32 offset=0)=0;
			virtual Void setProgram(IGAProgram * program)=0;
			virtual Void setProgramParameter(IGAProgramParameter * parameter)=0;
			virtual Void setPrimitiveTopology(IGAEnum::EPrimitiveTopology primitiveTopology)=0;
			virtual Void setRasterizerState(IGARasterizerState * state)=0;
			virtual Void setDepthStencilState(IGADepthStencilState * state,UInt32 stencilRef)=0;
			virtual Void setBlendState(IGABlendState * state,const Float factor[4],UInt32 samplerMask=-1)=0;
			virtual Void setScissorRects(UInt32 numRects,const CRect * rects)=0;
			virtual Void setViewports(UInt32 numViewports,const IGAStruct::SViewport * viewports)=0;
			virtual Void draw(UInt32 vertexCountPerInstance,UInt32 startVertexLocation,UInt32 instanceCount=1,UInt32 startInstanceLocation=0)=0;
			virtual Void draw(UInt32 indexCountPerInstance,UInt32 startIndexLocation,Int32 baseVertexLocation,UInt32 instanceCount=1,UInt32 startInstanceLocation=0)=0;
		};
	}
}