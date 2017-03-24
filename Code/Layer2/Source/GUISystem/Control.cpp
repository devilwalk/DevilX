#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::CControl::CControl(const String & name,NSUISystem::IGraphicScene * graphicScene,NSUISystem::IEventScene * eventScene)
	:mGraphicScene(graphicScene)
	,mEventScene(eventScene)
	,mParent(nullptr)
	,mLayer(nullptr)
	,mEventWindow(nullptr)
{
	mLayer=NSUISystem::getSystem()->createLayer(name);
}

NSDevilX::NSGUISystem::CControl::CControl(const String & name,CControl * parent)
	:mGraphicScene(parent->getGraphicScene())
	,mEventScene(parent->getEventScene())
	,mParent(parent)
	,mLayer(nullptr)
	,mEventWindow(nullptr)
{
	mLayer=NSUISystem::getSystem()->createLayer(name);
	getLayer()->setParent(getParent()->getLayer());
}

NSDevilX::NSGUISystem::CControl::~CControl()
{
	_destroyGraphicWindows();
	_destroyEventWindow();
	NSUISystem::getSystem()->destroyLayer(mLayer);
}

Void NSDevilX::NSGUISystem::CControl::_attachWindow(NSUISystem::IGraphicWindow * window)
{
	window->queryInterface_IElement()->setParent(getLayer());
	mGraphicWindows.push_back(window);
}

Void NSDevilX::NSGUISystem::CControl::_attachWindow(NSUISystem::IEventWindow * window)
{
	_destroyEventWindow();
	window->queryInterface_IElement()->setParent(getLayer());
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
	getEventScene()->destroyWindow(mEventWindow);
	mEventWindow=nullptr;
}
