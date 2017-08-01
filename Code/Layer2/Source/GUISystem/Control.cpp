#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::CControl::CControl(const String & name,NSUISystem::IGraphicScene * graphicScene,NSUISystem::IEventScene * eventScene)
	:mGraphicScene(graphicScene)
	,mEventScene(eventScene)
	,mCoordParent(nullptr)
	,mOrderParent(nullptr)
	,mLayer(nullptr)
	,mEventWindow(nullptr)
{
	mLayer=NSUISystem::getSystem()->createLayer(name);
	getLayer()->setSize(CFloat2::sOne);
}

NSDevilX::NSGUISystem::CControl::CControl(const String & name,CControl * coordParent,CControl * orderParent)
	:mGraphicScene(coordParent->getGraphicScene())
	,mEventScene(coordParent->getEventScene())
	,mCoordParent(coordParent)
	,mOrderParent(orderParent)
	,mLayer(nullptr)
	,mEventWindow(nullptr)
{
	mLayer=NSUISystem::getSystem()->createLayer(name);
	getLayer()->setSize(CFloat2::sOne);
	getLayer()->setCoordParent(getCoordParent()->getLayer());
	getLayer()->setOrderParent(getOrderParent()->getLayer());
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
