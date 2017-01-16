#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CViewport::CViewport(CRenderTarget * renderTarget)
	:CConstantBufferContainer("cbViewport")
	,mRenderTarget(renderTarget)
	,mCamera(nullptr)
{
}

NSDevilX::NSRenderSystem::NSD3D11::CViewport::~CViewport()
{
}

Void NSDevilX::NSRenderSystem::NSD3D11::CViewport::setupMT(ID3D11DeviceContext1 * context)
{
	mRenderTarget->setupMT(context);
	context->RSSetViewports(1,&getInternal());
}

Boolean NSDevilX::NSRenderSystem::NSD3D11::CViewport::isFullViewport() const
{
	if(getInternal().TopLeftX||getInternal().TopLeftY)
		return false;
	UInt32 width=0;
	UInt32 height=0;
	mRenderTarget->getSize(width,height);
	if((getInternal().Width==width)
		&&(getInternal().Height==height)
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}
Void NSDevilX::NSRenderSystem::NSD3D11::CViewport::_updateConstantBuffer(Byte * buffer)
{
	auto offset=mConstantBuffer->getDescription()->getConstantDesc("gViewportSizeInPixel").StartOffset;
	memcpy(&buffer[offset],&CFloat2(static_cast<Float>(getInternal().Width),static_cast<Float>(getInternal().Height)),sizeof(CFloat2));
	offset=mConstantBuffer->getDescription()->getConstantDesc("gInverseViewportSizeInPixel").StartOffset;
	memcpy(&buffer[offset],&CFloat2(1.0f/getInternal().Width,1.0f/getInternal().Height),sizeof(CFloat2));
}