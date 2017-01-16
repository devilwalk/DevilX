#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGL4;

NSDevilX::NSRenderSystem::NSGL4::CViewport::CViewport(CRenderTarget * renderTarget)
	:CConstantBufferContainer("cbViewport")
	,mRenderTarget(renderTarget)
	,mCamera(nullptr)
{
}

NSDevilX::NSRenderSystem::NSGL4::CViewport::~CViewport()
{
}

Void NSDevilX::NSRenderSystem::NSGL4::CViewport::setup()
{
	mRenderTarget->setup();
	glViewport(getX(),getY(),getWidth(),getHeight());
}

Boolean NSDevilX::NSRenderSystem::NSGL4::CViewport::isFullViewport() const
{
	if(getX()||getY())
		return false;
	GLsizei width=0;
	GLsizei height=0;
	mRenderTarget->getSize(width,height);
	if((getWidth()==width)
		&&(getHeight()==height)
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}
Void NSDevilX::NSRenderSystem::NSGL4::CViewport::_updateConstantBuffer(Byte * buffer)
{
	auto offset=mConstantBuffer->getDescription()->getConstantDesc("gViewportSizeInPixel").mOffsetInBytes;
	memcpy(&buffer[offset],&CFloat2(static_cast<Float>(getWidth()),static_cast<Float>(getHeight())),sizeof(CFloat2));
	offset=mConstantBuffer->getDescription()->getConstantDesc("gInverseViewportSizeInPixel").mOffsetInBytes;
	memcpy(&buffer[offset],&CFloat2(1.0f/getWidth(),1.0f/getHeight()),sizeof(CFloat2));
}