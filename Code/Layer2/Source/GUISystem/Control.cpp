#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::CControl::CControl(const String & name,NSUISystem::IGraphicScene * graphicScene,NSUISystem::IEventScene * eventScene)
	:mGraphicScene(graphicScene)
	,mEventScene(eventScene)
	,mContainer(static_cast<CContainer*>(this))
	,mCoordParent(nullptr)
	,mOrderParent(nullptr)
	,mLayer(nullptr)
	,mEventWindow(nullptr)
{
	mLayer=NSUISystem::getSystem()->createLayer(name);
	getLayer()->setSize(CFloat2::sOne);
}

NSDevilX::NSGUISystem::CControl::CControl(const String & name,CControl * coordParent,CControl * orderParent,Bool createEventWindow)
	:mGraphicScene(coordParent->getGraphicScene())
	,mEventScene(coordParent->getEventScene())
	,mContainer(coordParent->mContainer)
	,mCoordParent(coordParent)
	,mOrderParent(orderParent)
	,mLayer(nullptr)
	,mEventWindow(nullptr)
{
	mLayer=NSUISystem::getSystem()->createLayer(name);
	getLayer()->setSize(CFloat2::sOne);
	getLayer()->setCoordParent(getCoordParent()->getLayer());
	getLayer()->setOrderParent(getOrderParent()->getLayer());
	if(createEventWindow)
	{
		auto event_window=getEventScene()->createWindow(name);
		event_window->queryInterface_IElement()->setPosition(CFloat2::sZero);
		event_window->queryInterface_IElement()->setSize(CFloat2::sOne);
		_attachWindow(event_window);
		getEventWindow()->registerListener(this,CEvent::EType_MouseMove);
	}
}

NSDevilX::NSGUISystem::CControl::~CControl()
{
	_destroyGraphicWindows();
	_destroyEventWindow();
	NSUISystem::getSystem()->destroyLayer(mLayer);
}

Void NSDevilX::NSGUISystem::CControl::setCoordParent(CControl * control)
{
	mCoordParent=control;
	getLayer()->setCoordParent(getCoordParent()->getLayer());
}

Void NSDevilX::NSGUISystem::CControl::setOrderParent(CControl * control)
{
	mOrderParent=control;
	getLayer()->setOrderParent(getOrderParent()->getLayer());
}

Void NSDevilX::NSGUISystem::CControl::_attachWindow(NSUISystem::IGraphicWindow * window)
{
	window->queryInterface_IElement()->setCoordParent(getLayer());
	window->queryInterface_IElement()->setOrderParent(getLayer());
	mGraphicWindows.push_back(window);
}

Void NSDevilX::NSGUISystem::CControl::_attachWindow(NSUISystem::IEventWindow * window)
{
	_destroyEventWindow();
	window->queryInterface_IElement()->setCoordParent(getLayer());
	window->queryInterface_IElement()->setOrderParent(getLayer());
	mEventWindow=window;
}

Void NSDevilX::NSGUISystem::CControl::_destroyGraphicWindows()
{
	for(auto window:mGraphicWindows)
		getGraphicScene()->destroyWindow(window);
	mGraphicWindows.clear();
}

Void NSDevilX::NSGUISystem::CControl::_destroyEventWindow()
{
	if(getEventWindow())
	{
		getEventScene()->destroyWindow(getEventWindow());
		mEventWindow=nullptr;
	}
}

Void NSDevilX::NSGUISystem::CControl::onEvent(NSUISystem::IEvent * e)
{
	switch(e->getType())
	{
	case CEvent::EType_MouseMove:
		mContainer->setPrepareFocusControl(this);
		break;
	}
}

NSDevilX::NSGUISystem::CContainer::~CContainer()
{
}

Void NSDevilX::NSGUISystem::CContainer::update()
{
	CEvent e(CEvent::EType_MouseMove);
	e.queryInterface_IElement()->setPosition(ISystemImp::getSingleton().getWindow()->getCursorPosition()/ISystemImp::getSingleton().getWindow()->getSize());
	e.queryInterface_IElement()->setSize(CInt2::sOne/ISystemImp::getSingleton().getWindow()->getSize());
	if(!mEventScene->route(&e))
	{
		setPrepareFocusControl(nullptr);
	}
}

Void NSDevilX::NSGUISystem::CContainer::setPrepareFocusControl(CControl * control)
{
	for(auto iter=mPrepareFocusControls.begin();mPrepareFocusControls.end()!=iter;)
	{
		auto ctrl=*iter;
		if(ctrl!=control)
		{
			ctrl->setPrepareFocus(False);
			++iter;
		}
		else
			iter=mPrepareFocusControls.erase(iter);
	}
	if(control)
		addPrepareFocusControl(control);
}

Void NSDevilX::NSGUISystem::CContainer::addPrepareFocusControl(CControl * control)
{
	if(!mPrepareFocusControls.has(control))
	{
		mPrepareFocusControls.insert(control);
		control->setPrepareFocus(True);
	}
}

Void NSDevilX::NSGUISystem::CContainer::removePrepareFocusControl(CControl * control)
{
	if(mPrepareFocusControls.remove(control))
	{
		control->setPrepareFocus(False);
	}
}

Void NSDevilX::NSGUISystem::CContainer::setFocusControl(CControl * control)
{
	for(auto iter=mFocusControls.begin();mFocusControls.end()!=iter;)
	{
		auto ctrl=*iter;
		if(ctrl!=control)
		{
			ctrl->setFocus(False);
			++iter;
		}
		else
			iter=mFocusControls.erase(iter);
	}
	if(control)
		addFocusControl(control);
}

Void NSDevilX::NSGUISystem::CContainer::addFocusControl(CControl * control)
{
	if(!mFocusControls.has(control))
	{
		mFocusControls.insert(control);
		control->setFocus(True);
	}
}

Void NSDevilX::NSGUISystem::CContainer::removeFocusControl(CControl * control)
{
	if(mFocusControls.remove(control))
	{
		control->setFocus(False);
	}
}
