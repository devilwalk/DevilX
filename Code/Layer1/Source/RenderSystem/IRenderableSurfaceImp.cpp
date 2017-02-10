#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;

NSDevilX::NSRenderSystem::IRenderableSurfaceImp::IRenderableSurfaceImp(const String & name)
	:mName(name)
	,mWidth(0)
	,mHeight(0)
	,mFormat(IEnum::ERenderableSurfaceFormat_R8G8B8A8)
{}

NSDevilX::NSRenderSystem::IRenderableSurfaceImp::~IRenderableSurfaceImp()
{}

IRenderTarget * NSDevilX::NSRenderSystem::IRenderableSurfaceImp::queryInterface_IRenderTarget() const
{
	return const_cast<IRenderableSurfaceImp*>(this);
}

const String & NSDevilX::NSRenderSystem::IRenderableSurfaceImp::getName() const
{
	// TODO: 在此处插入 return 语句
	return mName;
}

Void NSDevilX::NSRenderSystem::IRenderableSurfaceImp::setSize(UInt32 width,UInt32 height)
{
	if(getWidth()!=width||getHeight()!=height)
	{
		notify(EMessage_BeginSizeChange);
		mWidth=width;
		mHeight=height;
		notify(EMessage_EndSizeChange);
	}
}

UInt32 NSDevilX::NSRenderSystem::IRenderableSurfaceImp::getWidth() const
{
	return mWidth;
}

UInt32 NSDevilX::NSRenderSystem::IRenderableSurfaceImp::getHeight() const
{
	return mHeight;
}

Void NSDevilX::NSRenderSystem::IRenderableSurfaceImp::setFormat(IEnum::ERenderableSurfaceFormat format)
{
	if(format!=getFormat())
	{
		notify(EMessage_BeginFormatChange);
		mFormat=format;
		notify(EMessage_EndFormatChange);
	}
}

IEnum::ERenderableSurfaceFormat NSDevilX::NSRenderSystem::IRenderableSurfaceImp::getFormat() const
{
	return mFormat;
}
