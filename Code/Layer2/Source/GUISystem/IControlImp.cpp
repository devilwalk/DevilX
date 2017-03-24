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

const String & NSDevilX::NSGUISystem::IControlImp::getName() const
{
	// TODO: 在此处插入 return 语句
	return getControl()->getLayer()->getName();
}

Void NSDevilX::NSGUISystem::IControlImp::setPosition(const CFloat2 & position)
{
	getControl()->getLayer()->setPosition(position);
}

const CFloat2 & NSDevilX::NSGUISystem::IControlImp::getPosition() const
{
	// TODO: 在此处插入 return 语句
	return getControl()->getLayer()->getPosition();
}

Void NSDevilX::NSGUISystem::IControlImp::setSize(const CFloat2 & size)
{
	getControl()->getLayer()->setSize(size);
}

const CFloat2 & NSDevilX::NSGUISystem::IControlImp::getSize() const
{
	// TODO: 在此处插入 return 语句
	return getControl()->getLayer()->getSize();
}

IWindow * NSDevilX::NSGUISystem::IControlImp::getParentWindow() const
{
	return mParentWindow;
}
