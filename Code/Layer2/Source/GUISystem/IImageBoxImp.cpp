#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::IImageBoxImp::IImageBoxImp(const String & name,IWindowImp * window)
	:mControl(nullptr)
{
	auto internal_control=DEVILX_NEW CImageBox(name,static_cast<IControlImp*>(window->queryInterface_IControl())->getControl());
	internal_control->setOrderParent(static_cast<IControlImp*>(window->queryInterface_IControl())->getControl());
	mControl=DEVILX_NEW IControlImp(IControlImp::EType_ImageBox,internal_control,window);
}

NSDevilX::NSGUISystem::IImageBoxImp::~IImageBoxImp()
{
	DEVILX_DELETE(mControl);
}

IControl * NSDevilX::NSGUISystem::IImageBoxImp::queryInterface_IControl() const
{
	return mControl;
}

Void NSDevilX::NSGUISystem::IImageBoxImp::setBackground(NSResourceSystem::IResource * resource)
{
	static_cast<CImageBox*>(mControl->getControl())->setBackground(resource);
}

NSResourceSystem::IResource * NSDevilX::NSGUISystem::IImageBoxImp::getBackground() const
{
	return static_cast<CImageBox*>(mControl->getControl())->getBackground();
}