#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::CCommonControl::CCommonControl(const String & name,CControl * coordParent,CControl * orderParent)
	:CControl(name,coordParent,orderParent)
	,mTextControl(nullptr)
	,mImageControl(nullptr)
{
	mImageControl=DEVILX_NEW CImageBox(name+"/ImageControl",this,this);
	mTextControl=DEVILX_NEW CStaticText(name+"/TextControl",this,mImageControl);
	getTextControl()->getTextProperty()->setColour(CFloatRGBA::sBlack);
	getTextControl()->getLayer()->setOrder(getImageControl()->getLayer()->getOrder()+1);
}

NSDevilX::NSGUISystem::CCommonControl::~CCommonControl()
{
	DEVILX_DELETE(getImageControl());
	DEVILX_DELETE(getTextControl());
}
