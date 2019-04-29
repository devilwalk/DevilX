#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSDirectX;
using namespace NSVersion11;

NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::IGADeviceContextImp(ID3D11Device * device,Bool deferred)
{
	if(deferred)
	{
		device->CreateDeferredContext(0,&mInternal);
	}
	else
	{
		device->GetImmediateContext(&mInternal);
	}
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::~IGADeviceContextImp()
{
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::clear(IGADepthStencilView * view,UInt32 flags,Float depth,UInt8 stencil)
{
	mInternal->ClearDepthStencilView(static_cast<IGADepthStencilViewImp*>(view)->getInternal(),CUtility::mappingClearFlags(flags),depth,stencil);
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::clear(IGARenderTargetView * view,const Float colourRGBA[4])
{
	mInternal->ClearRenderTargetView(static_cast<IGARenderTargetViewImp*>(view)->getInternal(),colourRGBA);
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::clear(IGAUnorderedAccessView * view,const Float value[4])
{
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::clear(IGAUnorderedAccessView * view,const UInt32 value[4])
{
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::setRenderTargets(UInt32 numRenderTarget,IGARenderTargetView * const * renderTargetViews,IGADepthStencilView * depthStencilView,UInt32 uavStartSlot,UInt32 numUAV,IGAUnorderedAccessView * const * unorderedAccessViews,const UInt32 * uavInitialCounts)
{
	for(UInt32 i=0;i<numRenderTarget;++i)
	{
		mPointerCache[i]=static_cast<IGARenderTargetViewImp*>(renderTargetViews[i])->getInternal();
	}
	for(UInt32 i=0;i<numUAV;++i)
	{
		mPointerCache[i+numRenderTarget]=nullptr;
	}
	mInternal->OMSetRenderTargetsAndUnorderedAccessViews(numRenderTarget,reinterpret_cast<ID3D11RenderTargetView**>(&mPointerCache[0]),static_cast<IGADepthStencilViewImp*>(depthStencilView)->getInternal(),uavStartSlot,numUAV,reinterpret_cast<ID3D11UnorderedAccessView**>(&mPointerCache[numRenderTarget]),uavInitialCounts);
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::setInputLayout(IGAInputLayout * layout)
{
	mInternal->IASetInputLayout(static_cast<IGAInputLayoutImp*>(layout)->getInternal());
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::setVertexBuffer(UInt32 startSlot,UInt32 numBuffers,IGAVertexBuffer * const * buffers,const UInt32 * strides,const UInt32 * offsets)
{
	for(UInt32 i=0;i<numBuffers;++i)
		mPointerCache[i]=static_cast<IGABufferImp*>(buffers[i])->getInternal();
	mInternal->IASetVertexBuffers(startSlot,numBuffers,reinterpret_cast<ID3D11Buffer**>(&mPointerCache[0]),strides,offsets);
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::setIndexBuffer(IGAIndexBuffer * buffer,IGAEnum::EGIFormat format,UInt32 offset)
{
	mInternal->IASetIndexBuffer(static_cast<IGABufferImp*>(buffer)->getInternal(),CUtility::mapping(format),offset);
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::setProgram(IGAProgram * program,IGAProgramParameter * parameter)
{
	static_cast<IGAProgramImp*>(program)->apply(mInternal,static_cast<IGAProgramParameterImp*>(parameter));
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::setPrimitiveTopology(IGAEnum::EPrimitiveTopology primitiveTopology)
{
	mInternal->IASetPrimitiveTopology(CUtility::mapping(primitiveTopology));
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::setRasterizerState(IGARasterizerState * state)
{
	mInternal->RSSetState(static_cast<IGARasterizerStateImp*>(state)->getInternal());
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::setDepthStencilState(IGADepthStencilState * state,UInt32 stencilRef)
{
	mInternal->OMSetDepthStencilState(static_cast<IGADepthStencilStateImp*>(state)->getInternal(),stencilRef);
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::setBlendState(IGABlendState * state,const Float factor[4],UInt32 samplerMask)
{
	mInternal->OMSetBlendState(static_cast<IGABlendStateImp*>(state)->getInternal(),factor,samplerMask);
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::setScissorRects(UInt32 numRects,const CRect * rects)
{
	std::array<D3D11_RECT,8> d3d_rects;
	for(UInt32 i=0;i<numRects;++i)
	{
		d3d_rects[i].bottom=rects[i].mBottom;
		d3d_rects[i].top=rects[i].mTop;
		d3d_rects[i].left=rects[i].mLeft;
		d3d_rects[i].right=rects[i].mRight;
	}
	mInternal->RSSetScissorRects(numRects,&d3d_rects[0]);
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::setViewports(UInt32 numViewports,const IGAStruct::SViewport * viewports)
{
	std::array<D3D11_VIEWPORT,8> d3d_vps;
	for(UInt32 i=0;i<numViewports;++i)
	{
		d3d_vps[i].Height=viewports[i].Height;
		d3d_vps[i].MaxDepth=viewports[i].MaxDepth;
		d3d_vps[i].MinDepth=viewports[i].MinDepth;
		d3d_vps[i].TopLeftX=viewports[i].TopLeftX;
		d3d_vps[i].TopLeftY=viewports[i].TopLeftY;
		d3d_vps[i].Width=viewports[i].Width;
	}
	mInternal->RSSetViewports(numViewports,&d3d_vps[0]);
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::draw(UInt32 vertexCountPerInstance,UInt32 startVertexLocation,UInt32 instanceCount,UInt32 startInstanceLocation)
{
	mInternal->DrawInstanced(vertexCountPerInstance,instanceCount,startVertexLocation,startInstanceLocation);
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::draw(UInt32 indexCountPerInstance,UInt32 startIndexLocation,Int32 baseVertexLocation,UInt32 instanceCount,UInt32 startInstanceLocation)
{
	mInternal->DrawIndexedInstanced(indexCountPerInstance,instanceCount,startIndexLocation,baseVertexLocation,startInstanceLocation);
}
