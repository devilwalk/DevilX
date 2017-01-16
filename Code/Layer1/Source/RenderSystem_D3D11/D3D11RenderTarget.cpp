#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CRenderTarget::CRenderTarget()
	:CConstantBufferContainer("cbRenderTarget")
	,mDepthStencil(nullptr)
{
	RtlSecureZeroMemory(mRenderTargets,sizeof(mRenderTargets));
}

NSDevilX::NSRenderSystem::NSD3D11::CRenderTarget::~CRenderTarget()
{
	for(auto i=0;i<8;++i)
		setRTView(i,nullptr);
	setDSView(nullptr);
}

Void NSDevilX::NSRenderSystem::NSD3D11::CRenderTarget::getSize(UInt32 & width,UInt32 & height)
{
	for(auto i=0;i<8;++i)
	{
		if(mRenderTargets[i])
		{
			CComPtr<ID3D11Texture2D> res;
			mRenderTargets[i]->GetResource(reinterpret_cast<ID3D11Resource**>(&res));
			D3D11_TEXTURE2D_DESC desc;
			res->GetDesc(&desc);
			width=desc.Width;
			height=desc.Height;
			break;
		}
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CRenderTarget::setRTView(UInt32 index,ID3D11RenderTargetView * view)
{
	if(mRenderTargets[index])
		mRenderTargets[index]->Release();
	mRenderTargets[index]=view;
	if(mRenderTargets[index])
		mRenderTargets[index]->AddRef();
}

Void NSDevilX::NSRenderSystem::NSD3D11::CRenderTarget::setDSView(ID3D11DepthStencilView * view)
{
	if(mDepthStencil)
		mDepthStencil->Release();
	mDepthStencil=view;
	if(mDepthStencil)
		mDepthStencil->AddRef();
}

Void NSDevilX::NSRenderSystem::NSD3D11::CRenderTarget::clearMT(UInt32 index,ID3D11DeviceContext1 * context,const CColour & colour)
{
	context->ClearRenderTargetView(mRenderTargets[index],reinterpret_cast<ConstFloatPtr>(&colour));
}

Void NSDevilX::NSRenderSystem::NSD3D11::CRenderTarget::clearMT(ID3D11DeviceContext1 * context,Float depth,Int32 stencil)
{
	UINT clear_flag=(depth>=0.0f?D3D11_CLEAR_DEPTH:0)|(stencil>=0?D3D11_CLEAR_STENCIL:0);
	context->ClearDepthStencilView(mDepthStencil,clear_flag,depth,static_cast<UInt8>(stencil));
}

Void NSDevilX::NSRenderSystem::NSD3D11::CRenderTarget::setupMT(ID3D11DeviceContext1 * context)
{
	context->OMSetRenderTargets(8,mRenderTargets,mDepthStencil);
}

Void NSDevilX::NSRenderSystem::NSD3D11::CRenderTarget::_updateConstantBuffer(Byte * buffer)
{
	UInt32 width=0;
	UInt32 height=0;
	getSize(width,height);
	auto offset=mConstantBuffer->getDescription()->getConstantDesc("gRenderTargetSizeInPixel").StartOffset;
	memcpy(&buffer[offset],&CFloat2(static_cast<Float>(width),static_cast<Float>(height)),sizeof(CFloat2));
	offset=mConstantBuffer->getDescription()->getConstantDesc("gInverseRenderTargetSizeInPixel").StartOffset;
	memcpy(&buffer[offset],&CFloat2(1.0f/width,1.0f/height),sizeof(CFloat2));
}
