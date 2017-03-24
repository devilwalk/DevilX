#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::ISceneImp::SEvent::SEvent()
	:mLayer(nullptr)
{
	mLayer=NSUISystem::getSystem()->createLayer("Scene/Focus");
}

NSDevilX::NSGUISystem::ISceneImp::SEvent::~SEvent()
{
	NSUISystem::getSystem()->destroyLayer(mLayer);
}

NSUISystem::IElement * NSDevilX::NSGUISystem::ISceneImp::SEvent::queryInterface_IElement() const
{
	return mLayer;
}

UInt32 NSDevilX::NSGUISystem::ISceneImp::SEvent::getType() const
{
	return -1;
}

NSDevilX::NSGUISystem::ISceneImp::ISceneImp(NSRenderSystem::IViewport * viewport)
	:mGraphicScene(nullptr)
	,mEventScene(nullptr)
	,mActiveWindow(nullptr)
{
	mGraphicScene=NSUISystem::getSystem()->createGraphicScene(viewport);
	mEventScene=NSUISystem::getSystem()->createEventScene(CStringConverter::toString(viewport));
}

NSDevilX::NSGUISystem::ISceneImp::~ISceneImp()
{
	NSUISystem::getSystem()->destroyGraphicScene(getGraphicScene());
	NSUISystem::getSystem()->destroyEventScene(getEventScene());
}

Void NSDevilX::NSGUISystem::ISceneImp::setActiveWindow(IWindowImp * window)
{
	if(window!=mActiveWindow)
	{
		mActiveWindow->setActive(False);
		mOrderedWindows.remove(mActiveWindow);
		mActiveWindow=window;
		mActiveWindow->setActive(True);
		mOrderedWindows.push_back(mActiveWindow);
		_updateWindowsOrder();
	}
}

NSRenderSystem::IViewport * NSDevilX::NSGUISystem::ISceneImp::getRenderViewport() const
{
	return getGraphicScene()->getRenderViewport();
}

IWindow * NSDevilX::NSGUISystem::ISceneImp::createWindow(const String & name)
{
	if(mWindows.has(name))
		return nullptr;
	auto window=DEVILX_NEW IWindowImp(name,this);
	static_cast<IControlImp*>(window->queryInterface_IControl())->getControl()->getLayer()->setOrder(static_cast<Int32>(mOrderedWindows.size()));
	mWindows.add(name,window);
	mOrderedWindows.push_back(window);
	return window;
}

IWindow * NSDevilX::NSGUISystem::ISceneImp::getWindow(const String & name) const
{
	return mWindows.get(name);
}

Void NSDevilX::NSGUISystem::ISceneImp::destroyWindow(IWindow * window)
{
	mWindows.destroy(window->queryInterface_IControl()->getName());
}

Void NSDevilX::NSGUISystem::ISceneImp::_updateWindowsOrder()
{
	Int32 order=0;
	for(auto window:mOrderedWindows)
	{
		static_cast<IControlImp*>(window->queryInterface_IControl())->getControl()->getLayer()->setOrder(order);
		++order;
	}
}

Void NSDevilX::NSGUISystem::ISceneImp::onMouseButtonEvent(CWindow * window,EMouseButtonType buttonType,EMouseButtonEventType eventType,const CUInt2 & position)
{
	SEvent e;
	e.queryInterface_IElement()->setPosition(position/window->getSize());
	e.queryInterface_IElement()->setSize(CInt2::sOne/window->getSize());
	getEventScene()->route(&e);
}
