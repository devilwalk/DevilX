#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGLES3;

NSDevilX::NSRenderSystem::NSGLES3::COverlayManager::COverlayManager(CViewportImp * viewport)
	:mViewport(viewport)
{
	mViewport->getInterfaceImp()->addListener(static_cast<TMessageReceiver<IViewportImp>*>(this),IViewportImp::EMessage_EndOverlayElementCreate);
	mViewport->getInterfaceImp()->addListener(static_cast<TMessageReceiver<IViewportImp>*>(this),IViewportImp::EMessage_BeginOverlayElementDestroy);
}

NSDevilX::NSRenderSystem::NSGLES3::COverlayManager::~COverlayManager()
{

}

Void NSDevilX::NSRenderSystem::NSGLES3::COverlayManager::render()
{
	mViewport->getInternal()->setup();
	CRenderOperation ro;
	for(auto const & renderables:mRenderables)
	{
		for(auto renderable:renderables.second)
		{
			if(renderable->render(ro))
			{
				ro.process();
				ro.mScissorRects.clear();
			}
		}
	}
}

Void NSDevilX::NSRenderSystem::NSGLES3::COverlayManager::onMessage(IViewportImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IViewportImp::EMessage_EndOverlayElementCreate:
	{
		auto renderable=_getRenderable(static_cast<IOverlayElementImp*>(data));
		renderable->addElement(static_cast<IOverlayElementImp*>(data));
		static_cast<IOverlayElementImp*>(data)->addListener(static_cast<TMessageReceiver<IOverlayElementImp>*>(this),IOverlayElementImp::EMessage_EndTextureUnitStateCreate);
		static_cast<IOverlayElementImp*>(data)->addListener(static_cast<TMessageReceiver<IOverlayElementImp>*>(this),IOverlayElementImp::EMessage_BeginOrderChange);
		static_cast<IOverlayElementImp*>(data)->addListener(static_cast<TMessageReceiver<IOverlayElementImp>*>(this),IOverlayElementImp::EMessage_EndOrderChange);
		static_cast<IOverlayElementImp*>(data)->addListener(static_cast<TMessageReceiver<IOverlayElementImp>*>(this),IOverlayElementImp::EMessage_BeginScissorRectChange);
		static_cast<IOverlayElementImp*>(data)->addListener(static_cast<TMessageReceiver<IOverlayElementImp>*>(this),IOverlayElementImp::EMessage_EndScissorRectChange);
	}
	break;
	case IViewportImp::EMessage_BeginOverlayElementDestroy:
	{
		auto renderable=_getRenderable(static_cast<IOverlayElementImp*>(data));
		renderable->removeElement(static_cast<IOverlayElementImp*>(data));
		static_cast<IOverlayElementImp*>(data)->removeListener(static_cast<TMessageReceiver<IOverlayElementImp>*>(this),IOverlayElementImp::EMessage_EndTextureUnitStateCreate);
		static_cast<IOverlayElementImp*>(data)->removeListener(static_cast<TMessageReceiver<IOverlayElementImp>*>(this),IOverlayElementImp::EMessage_BeginOrderChange);
		static_cast<IOverlayElementImp*>(data)->removeListener(static_cast<TMessageReceiver<IOverlayElementImp>*>(this),IOverlayElementImp::EMessage_EndOrderChange);
		static_cast<IOverlayElementImp*>(data)->removeListener(static_cast<TMessageReceiver<IOverlayElementImp>*>(this),IOverlayElementImp::EMessage_BeginScissorRectChange);
		static_cast<IOverlayElementImp*>(data)->removeListener(static_cast<TMessageReceiver<IOverlayElementImp>*>(this),IOverlayElementImp::EMessage_EndScissorRectChange);
	}
	break;
	}
}

Void NSDevilX::NSRenderSystem::NSGLES3::COverlayManager::onMessage(IOverlayElementImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IOverlayElementImp::EMessage_BeginOrderChange:
	case IOverlayElementImp::EMessage_BeginScissorRectChange:
	{
		auto renderable=_getRenderable(notifier);
		renderable->removeElement(notifier);
	}
	break;
	case IOverlayElementImp::EMessage_EndOrderChange:
	case IOverlayElementImp::EMessage_EndScissorRectChange:
	{
		auto renderable=_getRenderable(notifier);
		renderable->addElement(notifier);
	}
	break;
	case IOverlayElementImp::EMessage_EndTextureUnitStateCreate:
		static_cast<const IOverlayElementImp*>(notifier)->getTextureUnitState()->addListener(static_cast<TMessageReceiver<ITextureUnitStateImp>*>(this),ITextureUnitStateImp::EMessage_BeginTextureChange);
		static_cast<const IOverlayElementImp*>(notifier)->getTextureUnitState()->addListener(static_cast<TMessageReceiver<ITextureUnitStateImp>*>(this),ITextureUnitStateImp::EMessage_EndTextureChange);
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSGLES3::COverlayManager::onMessage(ITextureUnitStateImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	auto element=notifier->getUserPointer<IOverlayElementImp>(0);
	auto renderable=_getRenderable(element);
	switch(message)
	{
	case ITextureUnitStateImp::EMessage_BeginTextureChange:
		renderable->removeElement(element);
		break;
	case ITextureUnitStateImp::EMessage_EndTextureChange:
		renderable->addElement(element);
		break;
	}
}

COverlayRenderable * NSDevilX::NSRenderSystem::NSGLES3::COverlayManager::_getRenderable(IOverlayElementImp * element)
{
	auto material=CSystemImp::getSingleton().getOverlayMaterialManager()->getMaterial(element);
	COverlayRenderable * ret=nullptr;
	auto & renderables=mRenderables[element->getOrder()];
	for(auto renderable:renderables)
	{
		if((renderable->getMaterial()==material)
			&&(renderable->getScissorRectParameter()==CFloat4(element->getScissorRectPosition(),element->getScissorRectSize()))
			)
		{
			ret=renderable;
			break;
		}
	}
	if(!ret)
	{
		ret=DEVILX_NEW COverlayRenderable(material,element->getScissorRectPosition(),element->getScissorRectSize(),this);
		renderables.push_back(ret);
	}
	return ret;
}
