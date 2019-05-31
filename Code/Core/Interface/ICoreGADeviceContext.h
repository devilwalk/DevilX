#pragma once
#include "ICoreGAEnum.h"
#include "ICoreGAStruct.h"
#include "ICoreGAView.h"
#include "ICoreGAHighLevelResource.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class IGADeviceContextFeature_SeparateProgram
		{
		protected:
			virtual ~IGADeviceContextFeature_SeparateProgram()
			{
			}
		public:
			virtual Void setVertexShader(IGAVertexShader* shader,IGAShaderParameter* parameter)=0;
			virtual Void setPixelShader(IGAPixelShader* shader,IGAShaderParameter* parameter)=0;
			virtual Void setGeometryShader(IGAGeometryShader* shader,IGAShaderParameter* parameter)=0;
			virtual Void setHullShader(IGAHullShader* shader,IGAShaderParameter* parameter)=0;
			virtual Void setDomainShader(IGADomainShader* shader,IGAShaderParameter* parameter)=0;
		};
		class IGADeviceContextFeature_SeparateVAO
		{
		protected:
			virtual ~IGADeviceContextFeature_SeparateVAO()
			{
			}
		public:
			virtual Void setInputLayout(IGAInputLayout* layout)=0;
			virtual Void setVertexBuffer(UInt32 startSlot,UInt32 numBuffers,IGAVertexBuffer* const* buffers,const UInt32* strides,const UInt32* offsets=nullptr)=0;
		};
		class IGADeviceContextFeature_MultiDraw
		{
		protected:
			virtual ~IGADeviceContextFeature_MultiDraw()
			{
			}
		public:
			virtual Void draw(const TVector<IGAStruct::SDrawParameter_GL>& parameters)=0;
			virtual Void draw(const TVector<IGAStruct::SDrawIndexedParameter_GL>& parameters)=0;
		};
		class IGADeviceContextFeature_ComputeShader
		{
		protected:
			virtual ~IGADeviceContextFeature_ComputeShader()
			{
			}
		public:
			virtual Void clear(IGAUnorderedAccessView* view,const Float value[4])=0;
			virtual Void clear(IGAUnorderedAccessView* view,const UInt32 value[4])=0;
			virtual Void dispatch(IGAComputeShader* shader,IGAShaderParameter* parameter,UInt32 threadGroupCountX,UInt32 threadGroupCountY,UInt32 threadGroupCountZ)=0;
		};
		class IGADeviceContextFeature_IndirectDraw
		{
		protected:
			virtual ~IGADeviceContextFeature_IndirectDraw(){ }
		public:
			virtual Void drawIndirect(UInt32 vertexCountPerInstance,UInt32 startVertexLocation=0,UInt32 instanceCount=1,UInt32 startInstanceLocation=0)=0;
			virtual Void drawIndexedIndirect(UInt32 indexCountPerInstance,UInt32 startIndexLocation=0,Int32 baseVertexLocation=0,UInt32 instanceCount=1,UInt32 startInstanceLocation=0)=0;
		};
		class IGADeviceContext
		{
		protected:
			virtual ~IGADeviceContext()
			{
			}
		public:
			virtual IGADeviceContextFeature_SeparateProgram* queryFeature_SeparateProgram()const=0;
			virtual IGADeviceContextFeature_SeparateVAO* queryFeature_SeparateVAO()const=0;
			virtual IGADeviceContextFeature_MultiDraw* queryFeature_MultiDraw()const=0;
			virtual IGADeviceContextFeature_ComputeShader* queryFeature_ComputeShader()const=0;
			virtual Void update(IGAHighLevelBuffer* buffer,ConstVoidPtr data,UInt32 updateOffsetInBytes=0,UInt32 updateSizeInBytes=0)=0;
			virtual Void clear(IGADepthStencilView * view,UInt32 flags,Float depth,UInt8 stencil)=0;
			virtual Void clear(IGARenderTargetView * view,const Float colourRGBA[4])=0;
			virtual Void setRenderTargets(UInt32 numRenderTarget,IGARenderTargetView * const * renderTargetViews,IGADepthStencilView * depthStencilView)=0;
			virtual Void setVertexArrayObject(IGAVertexArrayObject * vao)=0;
			virtual Void setIndexBuffer(IGAIndexBuffer* buffer,IGAEnum::EIndexBufferFormat format,UInt32 offset=0)=0;
			virtual Void setProgram(IGAProgram * program,IGAProgramParameter * parameter)=0;
			virtual Void setPrimitiveTopology(IGAEnum::EPrimitiveTopology primitiveTopology)=0;
			virtual Void setRasterizerState(IGARasterizerState * state)=0;
			virtual Void setDepthStencilState(IGADepthStencilState * state,UInt32 stencilRef)=0;
			virtual Void setBlendState(IGABlendState * state,const Float factor[4],UInt32 samplerMask=-1)=0;
			virtual Void setScissorRects(UInt32 numRects,const CRect * rects)=0;
			virtual Void setViewports(UInt32 numViewports,const IGAStruct::SViewport * viewports)=0;
			virtual Void draw(UInt32 vertexCountPerInstance,UInt32 startVertexLocation=0,UInt32 instanceCount=1,UInt32 startInstanceLocation=0)=0;
			virtual Void drawIndexed(UInt32 indexCountPerInstance,UInt32 startIndexLocation=0,Int32 baseVertexLocation=0,UInt32 instanceCount=1,UInt32 startInstanceLocation=0)=0;
		};
	}
}