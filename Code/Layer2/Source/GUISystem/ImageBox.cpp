#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::CImageBox::CImageBox(const String & name,CControl * coordParent,CControl * orderParent)
	:CControl(name,coordParent,orderParent)
	,mBackground(nullptr)
{
	auto background=getGraphicScene()->createWindow(name);
	background->queryInterface_IElement()->setPosition(CFloat2::sZero);
	background->queryInterface_IElement()->setSize(CFloat2::sOne);
	background->setColour(CFloatRGBA::sWhite);
	_attachWindow(background);
	mBackground=DEVILX_NEW CGraphicWindowTextureUtility(background);
}

NSDevilX::NSGUISystem::CImageBox::~CImageBox()
{
	DEVILX_DELETE(mBackground);
}

Void NSDevilX::NSGUISystem::CImageBox::setBackground(NSResourceSystem::IResource * resource)
{
	mBackground->setTexture(resource);
}

NSResourceSystem::IResource * NSDevilX::NSGUISystem::CImageBox::getBackground() const
{
	return mBackground->getTextureResource();
}

Void NSDevilX::NSGUISystem::CImageBox::setBackgroundColour(const CColour & colour)
{
	mGraphicWindows[0]->setColour(colour);
}

const CColour & NSDevilX::NSGUISystem::CImageBox::getBackgroundColour() const
{
	// TODO: 在此处插入 return 语句
	return mGraphicWindows[0]->getColour();
}
