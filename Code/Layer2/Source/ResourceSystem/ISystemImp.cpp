#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSResourceSystem;
ISystem * NSDevilX::NSResourceSystem::getSystem()
{
	return ISystemImp::getSingletonPtr();
}

NSDevilX::NSResourceSystem::ISystemImp::ISystemImp()
	:mIOPool(nullptr)
	,mFontManager(nullptr)
{
	mIOPool=DEVILX_NEW CThreadPool(1);
	mFontManager=DEVILX_NEW CFontManager();
}

NSDevilX::NSResourceSystem::ISystemImp::~ISystemImp()
{
	DEVILX_DELETE(getIOPool());
	DEVILX_DELETE(mFontManager);
}

Void NSDevilX::NSResourceSystem::ISystemImp::update()
{
	notify(EMessage_Update);
}

IResource * NSDevilX::NSResourceSystem::ISystemImp::createResource(const String & name,const String & fileName)
{
	if(mResources.has(name))
		return nullptr;
	auto ret=DEVILX_NEW IResourceImp(name,fileName);
	mResources.add(name,ret);
	return ret;
}

IResource * NSDevilX::NSResourceSystem::ISystemImp::getResource(const String & name) const
{
	return mResources.get(name);
}

Void NSDevilX::NSResourceSystem::ISystemImp::destroyResource(IResource * res)
{
	return mResources.destroy(res->getName());
}

CImage * NSDevilX::NSResourceSystem::ISystemImp::getImage(ILoadedResource * resource)
{
	CImage * ret=nullptr;
	if(static_cast<IResourceImp*>(resource)->hasUserData("CImage"))
	{
		ret=static_cast<IResourceImp*>(resource)->getUserData("CImage").get<CImage*>();
	}
	else
	{
		ret=DEVILX_NEW CImage(static_cast<IResourceImp*>(resource)->getBuffer());
		static_cast<IResourceImp*>(resource)->setUserData("CImage",ret);
	}
	return ret;
}

CFontImage * NSDevilX::NSResourceSystem::ISystemImp::getFontImage(ILoadedResource * resource,const CUTF8Char & c,CUInt2 * pixelStart,CUInt2 * pixelEnd)
{
	CFontImage * ret=nullptr;
	if(static_cast<IResourceImp*>(resource)->hasUserData("CFontImage"))
	{
		ret=static_cast<IResourceImp*>(resource)->getUserData("CFontImage").get<CFontImage*>();
		ret->getPixelRange(static_cast<WChar>(c),pixelStart,pixelEnd);
	}
	else
	{
		ret=mFontManager->getImage(static_cast<IResourceImp*>(resource)->getFileName(),static_cast<WChar>(c),pixelStart,pixelEnd);
		static_cast<IResourceImp*>(resource)->setUserData("CFontImage",ret);
	}
	return ret;
}

NSRenderSystem::ITexture * NSDevilX::NSResourceSystem::ISystemImp::getRenderTexture(ILoadedResource * resource)
{
	NSRenderSystem::ITexture * ret=nullptr;
	if(static_cast<IResourceImp*>(resource)->hasUserData("NSRenderSystem::ITexture"))
	{
		ret=static_cast<IResourceImp*>(resource)->getUserData("NSRenderSystem::ITexture").get<NSRenderSystem::ITexture*>();
	}
	else
	{
		auto img=getImage(resource);
		ret=NSRenderSystem::getSystem()->queryInterface_IResourceManager()->createTexture(static_cast<IResourceImp*>(resource)->getFileName(),NSRenderSystem::IEnum::ETextureType_2D);
		ret->queryInterface_ITexture2DWritable()->setArraySize(1);
		switch(img->getPixelType())
		{
		case CImage::EPixelType_RGB8:
		case CImage::EPixelType_RGBA8:
			ret->queryInterface_ITexture2DWritable()->setFormat(NSRenderSystem::IEnum::ETexture2DFormat_R8G8B8A8);
			break;
		}
		ret->queryInterface_ITexture2DWritable()->setMipmapCount();
		ret->queryInterface_ITexture2DWritable()->setSize(img->getWidth(),img->getHeight());
		ret->queryInterface_ITexture2DWritable()->setPixels(img->getPixels());
		static_cast<IResourceImp*>(resource)->setUserData("NSRenderSystem::ITexture",ret);
	}
	return ret;
}

NSRenderSystem::ITexture * NSDevilX::NSResourceSystem::ISystemImp::getRenderTexture(ILoadedResource * resource,const CUTF8Char & c,CUInt2 * pixelStart,CUInt2 * pixelEnd)
{
	NSRenderSystem::ITexture * ret=nullptr;
	if(static_cast<IResourceImp*>(resource)->hasUserData("NSRenderSystem::ITexture"))
	{
		ret=static_cast<IResourceImp*>(resource)->getUserData("NSRenderSystem::ITexture").get<NSRenderSystem::ITexture*>();
	}
	else
	{
		auto img=getFontImage(resource,c,pixelStart,pixelEnd);
		ret=NSRenderSystem::getSystem()->queryInterface_IResourceManager()->createTexture("FontTexture/"+reinterpret_cast<SizeT>(img),NSRenderSystem::IEnum::ETextureType_2D);
		ret->queryInterface_ITexture2DWritable()->setArraySize(1);
		ret->queryInterface_ITexture2DWritable()->setFormat(NSRenderSystem::IEnum::ETexture2DFormat_A8);
		ret->queryInterface_ITexture2DWritable()->setMipmapCount();
		ret->queryInterface_ITexture2DWritable()->setSize(img->getSize().x,img->getSize().y);
		ret->queryInterface_ITexture2DWritable()->setPixels(img->getPixels());
		static_cast<IResourceImp*>(resource)->setUserData("NSRenderSystem::ITexture",ret);
	}
}

NSRenderSystem::IGeometry * NSDevilX::NSResourceSystem::ISystemImp::getRenderGeometry(ILoadedResource * resource)
{
	return nullptr;
}
