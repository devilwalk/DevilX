#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::CControl::CControl(const String & name,NSUISystem::IGraphicScene * graphicScene,NSUISystem::IEventScene * eventScene)
	:mGraphicScene(graphicScene)
	,mEventScene(eventScene)
	,mParent(nullptr)
	,mLayer(nullptr)
{
	mLayer=NSUISystem::getSystem()->createLayer(name);
}

NSDevilX::NSGUISystem::CControl::CControl(const String & name,CControl * parent)
	:mGraphicScene(parent->getGraphicScene())
	,mEventScene(parent->getEventScene())
	,mParent(parent)
	,mLayer(nullptr)
{
	mLayer=NSUISystem::getSystem()->createLayer(name);
	getLayer()->setParent(getParent()->getLayer());
}

NSDevilX::NSGUISystem::CControl::~CControl()
{
	_destroyGraphicWindows();
	NSUISystem::getSystem()->destroyLayer(mLayer);
}

Void NSDevilX::NSGUISystem::CControl::_attachGraphicWindow(NSUISystem::IGraphicWindow * window)
{
	window->queryInterface_IElement()->setParent(getLayer());
	mGraphicWindows.push_back(window);
}

Void NSDevilX::NSGUISystem::CControl::_destroyGraphicWindows()
{
	for(auto window:mGraphicWindows)
		getGraphicScene()->destroyWindow(window);
	mGraphicWindows.clear();
}
