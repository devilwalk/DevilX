#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::IStaticTextImp::IStaticTextImp(const String & name,IWindowImp * window)
	:mControl(nullptr)
{
	mControl=DEVILX_NEW IControlImp(IControlImp::EType_StaticText,DEVILX_NEW CStaticText(name,static_cast<IControlImp*>(window->queryInterface_IControl())->getControl()),window);

	mTextProperty=DEVILX_NEW ITextPropertyImp(static_cast<CStaticText*>(mControl->getControl())->getTextProperty());
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
	// TODO: �ڴ˴����� return ���
	return static_cast<CStaticText*>(mControl->getControl())->getText();
}