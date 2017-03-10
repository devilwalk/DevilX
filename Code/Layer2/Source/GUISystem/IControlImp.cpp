#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::IControlImp::IControlImp(const String & name,IWindowImp * parentWindow)
	:mName(name)
	,mParentWindow(parentWindow)
{
	mLayer=NSUISystem::getSystem()->createLayer(name);
}

NSDevilX::NSGUISystem::IControlImp::~IControlImp()
{
	for(auto window:mGraphicWindows)
		static_cast<ISceneImp*>(getParentWindow()->getScene())->getGraphicScene()->destroyWindow(window);
	NSUISystem::getSystem()->destroyLayer(mLayer);
}

Void NSDevilX::NSGUISystem::IControlImp::attachGraphicWindow(NSUISystem::IGraphicWindow * window)
{
	mGraphicWindows.push_back(window);
}

NSUISystem::IElement * NSDevilX::NSGUISystem::IControlImp::queryInterface_IElement() const
{
	return mLayer;
}

IWindow * NSDevilX::NSGUISystem::IControlImp::getParentWindow() const
{
	return mParentWindow;
}
