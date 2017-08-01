#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::IControlImp::IControlImp(EType type,CControl * control,IWindowImp * parentWindow)
	:mType(type)
	,mParentWindow(parentWindow)
	,mControl(control)
	,mParentControl(nullptr)
{
}

NSDevilX::NSGUISystem::IControlImp::~IControlImp()
{
	DEVILX_DELETE(getControl());
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

Void NSDevilX::NSGUISystem::IControlImp::setParent(IControl * control)
{
	if(control!=getParent())
	{
		mParentControl=static_cast<IControlImp*>(control);
		getControl()->setCoordParent(mParentControl->getControl());
		getControl()->setOrderParent(mParentControl->getControl());
	}
}

IControl * NSDevilX::NSGUISystem::IControlImp::getParent() const
{
	return mParentControl;
}

IWindow * NSDevilX::NSGUISystem::IControlImp::getParentWindow() const
{
	return mParentWindow;
}
