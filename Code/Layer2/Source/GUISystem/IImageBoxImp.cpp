#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::IImageBoxImp::IImageBoxImp(const String & name,IWindowImp * window)
	:mControl(nullptr)
{
	mControl=DEVILX_NEW IControlImp(IControlImp::EType_ImageBox,DEVILX_NEW CImageBox(name,static_cast<IControlImp*>(window->queryInterface_IControl())->getControl()),window);
	mControl->setUserPointer(0,this);
	mControl->addListener(static_cast<TMessageReceiver<IControlImp>*>(this),IControlImp::EMessage_BeginDestruction);
}

NSDevilX::NSGUISystem::IImageBoxImp::~IImageBoxImp()
{}

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

Void NSDevilX::NSGUISystem::IImageBoxImp::onMessage(IControlImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IControlImp::EMessage_BeginDestruction:
		DEVILX_DELETE(this);
		break;
	}
}
