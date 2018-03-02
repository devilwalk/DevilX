#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::CGraphicWindowTextureUtility::CGraphicWindowTextureUtility(NSUISystem::IGraphicWindow * graphicWindow)
	:mGraphicWindow(graphicWindow)
{}

NSDevilX::NSGUISystem::CGraphicWindowTextureUtility::~CGraphicWindowTextureUtility()
{}

Void NSDevilX::NSGUISystem::CGraphicWindowTextureUtility::setTexture(NSResourceSystem::IResource * resource,const CUInt2 & pixelStart,const CUInt2 & pixelEnd)
{
	if(resource!=mTextureResource)
	{
		mTextureResource=resource;
		mTextureResource->load(nullptr,True);
		mGraphicWindow->setTexture(NSResourceSystem::getSystem()->getRenderTexture(mTextureResource),pixelStart,pixelEnd);
	}
}