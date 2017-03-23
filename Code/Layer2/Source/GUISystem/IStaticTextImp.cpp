#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::IStaticTextImp::IStaticTextImp(const String & name,IWindowImp * window)
	:mControl(nullptr)
{
	mControl=DEVILX_NEW IControlImp(DEVILX_NEW CStaticText(name,static_cast<IControlImp*>(window->queryInterface_IControl())->getControl()),window);
	mControl->addListener(this,IControlImp::EMessage_BeginDestruction);
}

NSDevilX::NSGUISystem::IStaticTextImp::~IStaticTextImp()
{
}

IControl * NSDevilX::NSGUISystem::IStaticTextImp::queryInterface_IControl() const
{
	return mControl;
}

Void NSDevilX::NSGUISystem::IStaticTextImp::setFontResource(NSResourceSystem::IResource * resource)
{
	static_cast<CStaticText*>(mControl->getControl())->setFontResource(resource);
}

NSResourceSystem::IResource * NSDevilX::NSGUISystem::IStaticTextImp::getFontResource() const
{
	return static_cast<CStaticText*>(mControl->getControl())->getFontResource();
}

Void NSDevilX::NSGUISystem::IStaticTextImp::setText(const CUTF8String & text)
{
	static_cast<CStaticText*>(mControl->getControl())->setText(text);
}

const CUTF8String & NSDevilX::NSGUISystem::IStaticTextImp::getText() const
{
	// TODO: 在此处插入 return 语句
	return static_cast<CStaticText*>(mControl->getControl())->getText();
}

Void NSDevilX::NSGUISystem::IStaticTextImp::setTextColour(const CColour & colour)
{
	static_cast<CStaticText*>(mControl->getControl())->setTextColour(colour);
}

const CColour & NSDevilX::NSGUISystem::IStaticTextImp::getTextColour() const
{
	// TODO: 在此处插入 return 语句
	return static_cast<CStaticText*>(mControl->getControl())->getTextColour();
}

Void NSDevilX::NSGUISystem::IStaticTextImp::onMessage(IControlImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IControlImp::EMessage_BeginDestruction:
		DEVILX_DELETE(this);
		break;
	};
}
