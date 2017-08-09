#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::IStaticTextImp::IStaticTextImp(const String & name,IWindowImp * window)
	:mControl(nullptr)
{
	auto internal_control=DEVILX_NEW CStaticText(name,static_cast<IControlImp*>(window->queryInterface_IControl())->getControl());
	internal_control->setOrderParent(static_cast<IControlImp*>(window->queryInterface_IControl())->getControl());
	mControl=DEVILX_NEW IControlImp(IControlImp::EType_StaticText,internal_control,window);

	mTextProperty=DEVILX_NEW ITextPropertyImp();
	mTextProperty->add(static_cast<CStaticText*>(mControl->getControl())->getTextProperty());
}

NSDevilX::NSGUISystem::IStaticTextImp::~IStaticTextImp()
{
	DEVILX_DELETE(mControl);
	DEVILX_DELETE(mTextProperty);
}

IControl * NSDevilX::NSGUISystem::IStaticTextImp::queryInterface_IControl() const
{
	return mControl;
}

ITextProperty * NSDevilX::NSGUISystem::IStaticTextImp::getTextProperty() const
{
	return mTextProperty;
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