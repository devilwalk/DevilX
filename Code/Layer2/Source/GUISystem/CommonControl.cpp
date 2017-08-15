#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::CCommonControl::CCommonControl(const String & name,CControl * coordParent)
	:CControl(name,coordParent,False)
	,mTextControl(nullptr)
	,mImageControl(nullptr)
{
	mImageControl=DEVILX_NEW CImageBox(name+"/ImageControl",this);
	mImageControl->setOrderParent(this);
	mTextControl=DEVILX_NEW CStaticText(name+"/TextControl",this);
	mTextControl->setOrderParent(mImageControl);
	mTextControl->getTextProperty()->setColour(CFloatRGBA::sBlack);
}

NSDevilX::NSGUISystem::CCommonControl::~CCommonControl()
{
	DEVILX_DELETE(mImageControl);
	DEVILX_DELETE(mTextControl);
}

Void NSDevilX::NSGUISystem::CCommonControl::setVisible(Bool visible)
{
	mImageControl->setVisible(visible);
	mTextControl->setVisible(visible);
	CControl::setVisible(visible);
}

Void NSDevilX::NSGUISystem::CCommonControl::_setOrderChild(CControl * control)
{
	if(control==mImageControl)
	{
		CControl::_setOrderChild(control);
	}
	else
		control->setInternalOrderParent(mTextControl);
}
