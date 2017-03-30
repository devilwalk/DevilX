#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::CImageBox::CImageBox(const String & name,CControl * parent)
	:CControl(name,parent)
{
	auto background=getGraphicScene()->createWindow(name);
	background->queryInterface_IElement()->setPosition(CFloat2::sZero);
	background->queryInterface_IElement()->setSize(CFloat2::sOne);
	background->setColour(CFloatRGBA::sWhite);
	_attachWindow(background);
}

NSDevilX::NSGUISystem::CImageBox::~CImageBox()
{}

Void NSDevilX::NSGUISystem::CImageBox::setBackground(NSResourceSystem::IResource * resource)
{
	mBackgroundResource=resource;
}

NSResourceSystem::IResource * NSDevilX::NSGUISystem::CImageBox::getBackground() const
{
	return mBackgroundResource;
}
