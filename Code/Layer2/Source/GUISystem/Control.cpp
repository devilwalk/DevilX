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
	,mVisible(True)
	,mNotifier(nullptr)
{
	mNotifier=new CMessageNotifier;
	mLayer=NSUISystem::getSystem()->createLayer(name);
	getLayer()->setSize(CFloat2::sOne);
}

NSDevilX::NSGUISystem::CControl::CControl(const String & name,CControl * coordParent,Bool createEventWindow)
	:mGraphicScene(coordParent->getGraphicScene())
	,mEventScene(coordParent->getEventScene())
	,mContainer(coordParent->mContainer)
	,mCoordParent(nullptr)
	,mOrderParent(nullptr)
	,mLayer(nullptr)
	,mEventWindow(nullptr)
	,mVisible(True)
	,mNotifier(nullptr)
{
	mNotifier=new CMessageNotifier;
	mLayer=NSUISystem::getSystem()->createLayer(name);
	getLayer()->setSize(CFloat2::sOne);
	setCoordParent(coordParent);
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
	delete mNotifier;
}

Void NSDevilX::NSGUISystem::CControl::setCoordParent(CControl * control)
{
	mCoordParent=control;
	getLayer()->setCoordParent(getCoordParent()->getLayer());
}

Void NSDevilX::NSGUISystem::CControl::setOrderParent(CControl * control)
{
	if(control!=mOrderParent)
	{
		if(mOrderParent)
			mOrderParent->mNotifier->removeListener(this,EMessage_NeedRefreshOrderParent);
		mOrderParent=control;
		setInternalOrderParent(mOrderParent);
		if(mOrderParent)
			mOrderParent->mNotifier->addListener(this,EMessage_NeedRefreshOrderParent);
	}
}

Void NSDevilX::NSGUISystem::CControl::setInternalOrderParent(CControl * control)
{
	if(control)
		control->_setOrderChild(this);
	else
		getLayer()->setOrderParent(nullptr);
}

CUInt2 NSDevilX::NSGUISystem::CControl::getSizeInPixel() const
{
	return CUInt2(getLayer()->getDerivedSize()*ISystemImp::getSingleton().getWindow()->getSize());
}

Void NSDevilX::NSGUISystem::CControl::setVisible(Bool visible)
{
	mVisible=visible;
	for(auto window:mGraphicWindows)
		window->queryInterface_IElement()->setEnable(getVisible());
	if(getEventWindow())
		getEventWindow()->queryInterface_IElement()->setEnable(getVisible());
}

Void NSDevilX::NSGUISystem::CControl::_attachWindow(NSUISystem::IGraphicWindow * window)
{
	window->queryInterface_IElement()->setCoordParent(getLayer());
	window->queryInterface_IElement()->setOrderParent(getLayer());
	window->queryInterface_IElement()->setEnable(getVisible());
	mGraphicWindows.push_back(window);
}

Void NSDevilX::NSGUISystem::CControl::_attachWindow(NSUISystem::IEventWindow * window)
{
	_destroyEventWindow();
	window->queryInterface_IElement()->setCoordParent(getLayer());
	window->queryInterface_IElement()->setOrderParent(getLayer());
	window->queryInterface_IElement()->setEnable(getVisible());
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

Void NSDevilX::NSGUISystem::CControl::_setOrderChild(CControl * control)
{
	control->getLayer()->setOrderParent(getLayer());
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

Void NSDevilX::NSGUISystem::CControl::onMessage(CMessageNotifier * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case EMessage_NeedRefreshOrderParent:
		assert(mNotifier==notifier);
		setInternalOrderParent(getOrderParent());
		break;
	}
}

NSDevilX::NSGUISystem::CContainer::~CContainer()
{
	setPrepareFocusControl(nullptr);
	setFocusControl(nullptr);
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
			iter=mPrepareFocusControls.erase(iter);
		}
		else
			++iter;
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
			iter=mFocusControls.erase(iter);
		}
		else
			++iter;
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
