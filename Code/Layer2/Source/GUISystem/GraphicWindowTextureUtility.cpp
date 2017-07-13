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
		struct SLoad
			:public TBaseObject<SLoad>
			,public NSResourceSystem::ILoadCallback
		{
			NSRenderSystem::ITexture * mTexture;
			SLoad()
				:mTexture(nullptr)
			{

			}
			virtual Void onLoaded(NSResourceSystem::ILoadedResource * resource)
			{
				mTexture=NSResourceSystem::getSystem()->getRenderTexture(resource);
			}
		};
		SLoad load_call_back;
		mTextureResource->load(&load_call_back,True);
		mGraphicWindow->setTexture(load_call_back.mTexture,pixelStart,pixelEnd);
	}
}