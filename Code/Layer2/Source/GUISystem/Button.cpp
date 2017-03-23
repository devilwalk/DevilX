#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::CButton::CButton(const String & name,CControl * parent)
	:CControl(name,parent)
	,mTextControl(nullptr)
	,mBackgroundResource(nullptr)
{
	auto background=getGraphicScene()->createWindow(name+"/Background");
	background->queryInterface_IElement()->setPosition(CFloat2::sZero);
	background->queryInterface_IElement()->setSize(CFloat2::sOne);
	attachGraphicWindow(background);
	mTextControl=DEVILX_NEW CStaticText(name+"/TextControl",this);
}

NSDevilX::NSGUISystem::CButton::~CButton()
{
	DEVILX_DELETE(getTextControl());
}

Void NSDevilX::NSGUISystem::CButton::setBackground(NSResourceSystem::IResource * resource)
{
	mBackgroundResource=resource;
}

NSResourceSystem::IResource * NSDevilX::NSGUISystem::CButton::getBackground() const
{
	return mBackgroundResource;
}
