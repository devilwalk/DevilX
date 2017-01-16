#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
NSDevilX::NSRenderSystem::IRenderTargetImp::IRenderTargetImp()
	:mWidth(0)
	,mHeight(0)
{}

NSDevilX::NSRenderSystem::IRenderTargetImp::~IRenderTargetImp()
{
}

UInt32 NSDevilX::NSRenderSystem::IRenderTargetImp::getWidth() const
{
	return mWidth;
}

UInt32 NSDevilX::NSRenderSystem::IRenderTargetImp::getHeight() const
{
	return mHeight;
}

IViewport * NSDevilX::NSRenderSystem::IRenderTargetImp::createViewport(const String & name)
{
	if(mViewports.has(name))
		return nullptr;
	notify(EMessage_BeginViewportCreate);
	IViewportImp * viewport=DEVILX_NEW IViewportImp(name,this);
	mOrders[viewport->getOrder()].insert(mViewports.size());
	mViewports.add(name,viewport);
	viewport->addListener(this,IViewportImp::EMessage_BeginOrderChange);
	viewport->addListener(this,IViewportImp::EMessage_EndOrderChange);
	notify(EMessage_EndViewportCreate,viewport);
	return viewport;
}

Void NSDevilX::NSRenderSystem::IRenderTargetImp::destroyViewport(IViewport * viewport)
{
	if(!mViewports.has(viewport->getName()))
		return;
	notify(EMessage_BeginViewportDestroy,static_cast<IViewportImp*>(viewport));
	mOrders[viewport->getOrder()].erase(mViewports.getIndex(viewport->getName()));
	mViewports.destroy(viewport->getName());
	notify(EMessage_EndViewportDestroy,static_cast<IViewportImp*>(viewport));
}

IViewport * NSDevilX::NSRenderSystem::IRenderTargetImp::getViewport(const String & name) const
{
	return mViewports.get(name);
}

Void NSDevilX::NSRenderSystem::IRenderTargetImp::setClearColour(const CColour & colour)
{
	if(colour!=mClearColour)
	{
		notify(EMessage_BeginClearColourChange);
		mClearColour=colour;
		notify(EMessage_EndClearColourChange);
	}
}

const CColour & NSDevilX::NSRenderSystem::IRenderTargetImp::getClearColour() const
{
	// TODO: insert return statement here
	return mClearColour;
}

Void NSDevilX::NSRenderSystem::IRenderTargetImp::onMessage(IViewportImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IViewportImp::EMessage_BeginOrderChange:
		mOrders[notifier->getOrder()].erase(mViewports.getIndex(notifier->getName()));
		break;
	case IViewportImp::EMessage_EndOrderChange:
		mOrders[notifier->getOrder()].insert(mViewports.getIndex(notifier->getName()));
		break;
	}
}

NSDevilX::NSRenderSystem::IWindowImp::IWindowImp(VoidPtr handle)
	:mHandle(handle)
{}

NSDevilX::NSRenderSystem::IWindowImp::~IWindowImp()
{}

IRenderTarget * NSDevilX::NSRenderSystem::IWindowImp::queryInterface_IRenderTarget() const
{
	return const_cast<IWindowImp*>(this);
}

Void NSDevilX::NSRenderSystem::IWindowImp::resize()
{
	notify(EMessage_Resize);
}