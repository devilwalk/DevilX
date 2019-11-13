#pragma once
#include "ICommonGraphicsAPIBuffer.h"
#include "ICommonGraphicsAPIFrameBufferObject.h"
#include "ICommonGraphicsAPIHeap.h"
#include "ICommonGraphicsAPIInputLayout.h"
#include "ICommonGraphicsAPIPipelineState.h"
#include "ICommonGraphicsAPIShader.h"
#include "ICommonGraphicsAPIShaderResourceView.h"
#include "ICommonGraphicsAPITexture.h"
#include "ICommonGraphicsAPIUnorderedAccessView.h"
#include "ICommonGraphicsAPIVertexArrayObject.h"
namespace NSDevilX
{
	namespace NSGraphicsAPI
	{
		class ICommandBuffer
		{
		protected:
			virtual ~ICommandBuffer()
			{
			}
		public:
		};

		class IIndirectCommandList;
		class ICommandList
		{
		protected:
			virtual ~ICommandList()
			{
			}
		public:
			virtual Void execute(ICommandBuffer* buffer)=0;
			virtual Void finish(OUT ICommandBuffer* buffer)=0;
			//d3d9 style
			virtual Void lock(IBuffer* buffer,UINT offsetToLock,UINT sizeToLock,OUT VOID** data,DWORD flags)=0;
			virtual Void unlock(IBuffer* buffer)=0;
			virtual Void lockRect(ISurface* surface,OUT D3DLOCKED_RECT* lockedRect,const RECT* rect,DWORD flags)=0;
			virtual Void lockRect(ITexture* texture,UINT level,OUT D3DLOCKED_RECT* lockedRect,const RECT* rect,DWORD flags)=0;
			virtual Void lockRect(ITexture* texture,D3DCUBEMAP_FACES faceType,UINT level,OUT D3DLOCKED_RECT* lockedRect,const RECT* rect,DWORD flags)=0;
			virtual Void unlockRect(ISurface* surface)=0;
			virtual Void unlockRect(ITexture* texture)=0;
			//d3d10/11 style
			virtual Void map(IBuffer* buffer,D3D10_MAP mapType,UINT mapFlags,OUT Void** data)=0;
			virtual Void map(ITexture* texture,UINT subResource,D3D11_MAP mapType,UINT mapFlags,OUT Void** data)=0;
			virtual Void map(ITexture* texture,UINT subResource,D3D11_MAP mapType,UINT mapFlags,OUT D3D10_MAPPED_TEXTURE2D* data)=0;
			virtual Void map(ITexture* texture,UINT subResource,D3D11_MAP mapType,UINT mapFlags,OUT D3D10_MAPPED_TEXTURE3D* data)=0;
			virtual Void map(IBuffer* resource,UINT subResource,D3D11_MAP mapType,UINT mapFlags,OUT D3D11_MAPPED_SUBRESOURCE* mappedResource)=0;
			virtual Void map(ITexture* resource,UINT subResource,D3D11_MAP mapType,UINT mapFlags,OUT D3D11_MAPPED_SUBRESOURCE* mappedResource)=0;
			virtual Void unmap(IBuffer* resource)=0;
			virtual Void unmap(ITexture* resource,UINT subResource)=0;
			//d3d9 style
			virtual Void beginScene()=0;
			virtual Void clear(DWORD count,const D3DRECT* rects,DWORD flags,D3DCOLOR color,float z,DWORD stencil)=0;
			virtual Void setRenderTarget(DWORD renderTargetIndex,ISurface* renderTarget)=0;
			virtual Void setDepthStencilSurface(ISurface* newZStencil)=0;
			virtual Void setViewport(const D3DVIEWPORT9& viewport)=0;
			virtual Void setVertexDeclaration(IInputLayout* layout)=0;
			virtual Void setStreamSource(UINT streamNumber,IBuffer* streamData,UINT offsetInBytes,UINT stride)=0;
			virtual Void setStreamSourceFreq(UINT streamNumber,UINT frequencyParameter)=0;
			virtual Void setIndices(IBuffer* indexData)=0;
			virtual Void setVertexShader(IShader* shader)=0;
			virtual Void setVertexShaderConstantB(UINT startRegister,const BOOL* constantData,UINT boolCount)=0;
			virtual Void setVertexShaderConstantF(UINT startRegister,const Float* constantData,UINT vector4fCount)=0;
			virtual Void setVertexShaderConstantI(UINT startRegister,const Int32* constantData,UINT vector4iCount)=0;
			virtual Void setPixelShader(IShader* shader)=0;
			virtual Void setPixelShaderConstantB(UINT startRegister,const BOOL* constantData,UINT boolCount)=0;
			virtual Void setPixelShaderConstantF(UINT startRegister,const Float* constantData,UINT vector4fCount)=0;
			virtual Void setPixelShaderConstantI(UINT startRegister,const Int32* constantData,UINT vector4iCount)=0;
			virtual Void setTexture(DWORD sampler,ITexture* texture)=0;
			virtual Void setRenderState(D3DRENDERSTATETYPE state,DWORD value)=0;
			virtual Void setTextureStageState(DWORD stage,D3DTEXTURESTAGESTATETYPE type,DWORD value)=0;
			virtual Void applyStateBlock(IStateBlock* stateBlock)=0;
			virtual Void drawPrimitive(D3DPRIMITIVETYPE type,UINT startVertex,UINT primitiveCount)=0;
			virtual Void drawIndexedPrimitive(D3DPRIMITIVETYPE type,INT baseVertexIndex,UINT minIndex,UINT numVertices,UINT startIndex,UINT primitiveCount)=0;
			virtual Void endScene()=0;
			//d3d10/11 style
			virtual Void clearRenderTargetView(IRenderTargetView* view,const FLOAT colorRGBA[4])=0;
			virtual Void clearDepthStencilView(IDepthStencilView* view,UINT clearFlags,FLOAT depth,UINT8 stencil)=0;
			virtual Void clearState()=0;
			virtual Void clearUnorderedAccessViewFloat(IUnorderedAccessView* view,const FLOAT value[4])=0;
			virtual Void clearUnorderedAccessViewUint(IUnorderedAccessView* view,const UINT value[4])=0;
			virtual Void iaSetInputLayout(IInputLayout* layout)=0;
			virtual Void iaSetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY topology)=0;
			virtual Void iaSetVertexBuffers(UINT startSlot,UINT numBuffers,IBuffer*const* vertexBuffers,const UINT* strides,const UINT* offsets)=0;
			virtual Void iaSetIndexBuffers(IBuffer* indexBuffer,DXGI_FORMAT format,UINT offset)=0;
			virtual Void vsSetShader(IShader* shader)=0;
			virtual Void vsSetConstantBuffers(UINT startSlot,UINT numBuffers,IBuffer* const* constantBuffers)=0;
			virtual Void vsSetShaderResource(UINT startSlot,UINT numViews,IShaderResourceView* const* shaderResourceViews)=0;
			virtual Void vsSetSamplers(UINT startSlot,UINT numSamplers,ISamplerState*const* samplers)=0;
			virtual Void hsSetShader(IShader* shader)=0;
			virtual Void hsSetConstantBuffers(UINT startSlot,UINT numBuffers,IBuffer* const* constantBuffers)=0;
			virtual Void hsSetShaderResource(UINT startSlot,UINT numViews,IShaderResourceView* const* shaderResourceViews)=0;
			virtual Void hsSetSamplers(UINT startSlot,UINT numSamplers,ISamplerState* const* samplers)=0;
			virtual Void dsSetShader(IShader* shader)=0;
			virtual Void dsSetConstantBuffers(UINT startSlot,UINT numBuffers,IBuffer* const* constantBuffers)=0;
			virtual Void dsSetShaderResource(UINT startSlot,UINT numViews,IShaderResourceView* const* shaderResourceViews)=0;
			virtual Void dsSetSamplers(UINT startSlot,UINT numSamplers,ISamplerState* const* samplers)=0;
			virtual Void gsSetShader(IShader* shader)=0;
			virtual Void gsSetConstantBuffers(UINT startSlot,UINT numBuffers,IBuffer* const* constantBuffers)=0;
			virtual Void gsSetShaderResource(UINT startSlot,UINT numViews,IShaderResourceView* const* shaderResourceViews)=0;
			virtual Void gsSetSamplers(UINT startSlot,UINT numSamplers,ISamplerState* const* samplers)=0;
			virtual Void rsSetViewports(UINT numViewports,const D3D10_VIEWPORT* viewports)=0;
			virtual Void rsSetViewports(UINT numViewports,const D3D11_VIEWPORT* viewports)=0;
			virtual Void rsSetState(IRasterizerState* state)=0;
			virtual Void psSetShader(IShader* shader)=0;
			virtual Void psSetConstantBuffers(UINT startSlot,UINT numBuffers,IBuffer* const* constantBuffers)=0;
			virtual Void psSetShaderResource(UINT startSlot,UINT numViews,IShaderResourceView* const* shaderResourceViews)=0;
			virtual Void psSetSamplers(UINT startSlot,UINT numSamplers,ISamplerState* const* samplers)=0;
			virtual Void omSetRenderTargets(UINT numViews,IRenderTargetView* const* renderTargetViews,IDepthStencilView* depthStencilView)=0;
			virtual Void omSetRenderTargetsAndUnorderedAccessViews(UINT numViews,IRenderTargetView* const* renderTargetViews,IDepthStencilView* depthStencilView,UINT uavStartSlot,UINT numUAVs,IUnorderedAccessView* const* unorderedAccessViews,const UINT* uavInitialCounts)=0;
			virtual Void omSetDepthStencilState(IDepthStencilState* depthStencilState)=0;
			virtual Void omSetBlendState(IBlendState* blendState,const FLOAT blendFactor[4],UINT sampleMask)=0;
		};

		class IDirectCommandList
		{
		protected:
			virtual ~IDirectCommandList()
			{
			}
		public:
			virtual ICommandList* queryInterface_ICommandList()const=0;
		};

		class IIndirectCommandList
		{
		protected:
			virtual ~IIndirectCommandList()
			{
			}
		public:
			virtual ICommandList* queryInterface_ICommandList()const=0;
		};

		class ICommandDriver
		{
		protected:
			virtual ~ICommandDriver(){ }
		public:
			virtual IDirectCommandList* getDirectCommandList()const=0;
			virtual Void execute(ICommandList* cmdList)=0;
		};
	}
}