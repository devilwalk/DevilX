#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::IButtonImp::IButtonImp(const String & name,IWindowImp * window)
	:mControl(nullptr)
{
	mControl=DEVILX_NEW IControlImp(DEVILX_NEW CButton(name,static_cast<IControlImp*>(window->queryInterface_IControl())->getControl()),window);
}

NSDevilX::NSGUISystem::IButtonImp::~IButtonImp()
{
	DEVILX_DELETE(mControl);
}

IControl * NSDevilX::NSGUISystem::IButtonImp::queryInterface_IControl() const
{
	return mControl;
}

Void NSDevilX::NSGUISystem::IButtonImp::setFontResource(NSResourceSystem::IResource * resource)
{
	static_cast<CButton*>(mControl->getControl())->getTextControl()->setFontResource(resource);
}

NSResourceSystem::IResource * NSDevilX::NSGUISystem::IButtonImp::getFontResource() const
{
	return static_cast<CButton*>(mControl->getControl())->getTextControl()->getFontResource();
}

Void NSDevilX::NSGUISystem::IButtonImp::setText(const CUTF8String & text)
{
	static_cast<CButton*>(mControl->getControl())->getTextControl()->setText(text);
}

const CUTF8String & NSDevilX::NSGUISystem::IButtonImp::getText() const
{
	// TODO: 在此处插入 return 语句
	return static_cast<CButton*>(mControl->getControl())->getTextControl()->getText();
}

Void NSDevilX::NSGUISystem::IButtonImp::setTextColour(const CColour & colour)
{
	static_cast<CButton*>(mControl->getControl())->getTextControl()->setTextColour(colour);
}

const CColour & NSDevilX::NSGUISystem::IButtonImp::getTextColour() const
{
	// TODO: 在此处插入 return 语句
	return static_cast<CButton*>(mControl->getControl())->getTextControl()->getTextColour();
}

Void NSDevilX::NSGUISystem::IButtonImp::setBackground(NSResourceSystem::IResource * resource)
{
	static_cast<CButton*>(mControl->getControl())->setBackground(resource);
}

NSResourceSystem::IResource * NSDevilX::NSGUISystem::IButtonImp::getBackground() const
{
	return static_cast<CButton*>(mControl->getControl())->getBackground();
}

Void NSDevilX::NSGUISystem::IButtonImp::setEventCallback(IButtonEventCallback * callback)
{
	return Void();
}

IButtonEventCallback * NSDevilX::NSGUISystem::IButtonImp::getEventCallback() const
{
	return nullptr;
}

Void NSDevilX::NSGUISystem::IButtonImp::onMessage(IControlImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IControlImp::EMessage_BeginDestruction:
		DEVILX_DELETE(this);
		break;
	}
}
