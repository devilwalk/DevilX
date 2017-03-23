#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::IControlImp::IControlImp(CControl * control,IWindowImp * parentWindow)
	:mParentWindow(parentWindow)
	,mControl(control)
{
}

NSDevilX::NSGUISystem::IControlImp::~IControlImp()
{
	notify(EMessage_BeginDestruction);
	DEVILX_DELETE(getControl());
	notify(EMessage_EndDestruction);
}

NSUISystem::IElement * NSDevilX::NSGUISystem::IControlImp::queryInterface_IElement() const
{
	return getControl()->getLayer();
}

IWindow * NSDevilX::NSGUISystem::IControlImp::getParentWindow() const
{
	return mParentWindow;
}
