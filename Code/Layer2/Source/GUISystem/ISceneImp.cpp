#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::ISceneImp::SEvent::SEvent(EType type)
	:mType(type)
	,mLayer(nullptr)
{
	mLayer=NSUISystem::getSystem()->createLayer("Scene/Focus/"+CStringConverter::toString(this));
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
	return mType;
}

NSDevilX::NSGUISystem::ISceneImp::ISceneImp(NSRenderSystem::IViewport * viewport)
	:mGraphicScene(nullptr)
	,mEventScene(nullptr)
	,mActiveWindow(nullptr)
{
	mGraphicScene=NSUISystem::getSystem()->createGraphicScene(viewport);
	mEventScene=NSUISystem::getSystem()->createEventScene(CStringConverter::toString(viewport));
	ISystemImp::getSingleton().getWindow()->registerEventListener(this);
}

NSDevilX::NSGUISystem::ISceneImp::~ISceneImp()
{
	mWindows.destroyAll();
	NSUISystem::getSystem()->destroyGraphicScene(getGraphicScene());
	NSUISystem::getSystem()->destroyEventScene(getEventScene());
	ISystemImp::getSingleton().getWindow()->unregisterEventListener(this);
}

Void NSDevilX::NSGUISystem::ISceneImp::update()
{
	if(mActiveWindow)
		mActiveWindow->update();
}

Void NSDevilX::NSGUISystem::ISceneImp::setActiveWindow(IWindowImp * window)
{
	if(mActiveWindow&&mActiveWindow->isModule()&&(!window->isModule()))
		return;
	if(window!=mActiveWindow)
	{
		if(mActiveWindow)
		{
			static_cast<CContainer*>(static_cast<IControlImp*>(mActiveWindow->queryInterface_IControl())->getControl())->setPrepareFocusControl(nullptr);
			static_cast<CContainer*>(static_cast<IControlImp*>(mActiveWindow->queryInterface_IControl())->getControl())->setFocusControl(nullptr);
		}
		if(window)
		{
			if(window->isModule())
				mOrderedModuleWindows.remove(window);
			else
				mOrderedWindows.remove(window);
		}
		mActiveWindow=window;
		if(window)
		{
			if(window->isModule())
				mOrderedModuleWindows.push_back(window);
			else
				mOrderedWindows.push_back(window);
			_updateWindowsOrder();
		}
	}
}

NSRenderSystem::IViewport * NSDevilX::NSGUISystem::ISceneImp::getRenderViewport() const
{
	return getGraphicScene()->getRenderViewport();
}

IWindow * NSDevilX::NSGUISystem::ISceneImp::createWindow(const String & name,Bool isModule)
{
	if(mWindows.has(name))
		return nullptr;
	auto window=DEVILX_NEW IWindowImp(name,this,isModule);
	static_cast<IControlImp*>(window->queryInterface_IControl())->getControl()->getLayer()->setOrder(isModule?static_cast<Int32>(static_cast<UInt16>(-1)+mOrderedModuleWindows.size()):static_cast<Int32>(mOrderedWindows.size()));
	mWindows.add(name,window);
	if(isModule)
		mOrderedModuleWindows.push_back(window);
	else
		mOrderedWindows.push_back(window);
	setActiveWindow(window);
	return window;
}

IWindow * NSDevilX::NSGUISystem::ISceneImp::getWindow(const String & name) const
{
	return mWindows.get(name);
}

Void NSDevilX::NSGUISystem::ISceneImp::destroyWindow(IWindow * window)
{
	if(mActiveWindow==window)
	{
		if(mActiveWindow->isModule())
			mOrderedModuleWindows.remove(mActiveWindow);
		else
			mOrderedWindows.remove(mActiveWindow);
		mActiveWindow=nullptr;
	}
	mWindows.destroy(window->queryInterface_IControl()->getName());
}

Void NSDevilX::NSGUISystem::ISceneImp::_updateWindowsOrder()
{
	Int32 order=static_cast<UInt16>(-1);
	for(auto window:mOrderedModuleWindows)
	{
		static_cast<IControlImp*>(window->queryInterface_IControl())->getControl()->getLayer()->setOrder(order);
		++order;
	}
	order=0;
	for(auto window:mOrderedWindows)
	{
		static_cast<IControlImp*>(window->queryInterface_IControl())->getControl()->getLayer()->setOrder(order);
		++order;
	}
}

Void NSDevilX::NSGUISystem::ISceneImp::onMouseButtonEvent(CWindow * window,EMouseButtonType buttonType,EMouseButtonEventType eventType,const CUInt2 & position)
{
	if(EMouseButtonEventType_Up==eventType)
	{
		SEvent e(SEvent::EType_WindowActive);
		e.queryInterface_IElement()->setPosition(position/window->getSize());
		e.queryInterface_IElement()->setSize(CInt2::sOne/window->getSize());
		getEventScene()->route(&e);
	}
}
