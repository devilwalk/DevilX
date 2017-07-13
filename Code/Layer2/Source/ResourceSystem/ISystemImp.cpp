#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSResourceSystem;
NSDevilX::NSResourceSystem::ISystem * NSDevilX::NSResourceSystem::getSystem()
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

Void NSDevilX::NSResourceSystem::ISystemImp::shutdown()
{
	DEVILX_DELETE(this);
}

IResource * NSDevilX::NSResourceSystem::ISystemImp::createResource(const String & name,const String & filename)
{
	if(mResources.has(name))
		return nullptr;
	auto ret=DEVILX_NEW IResourceImp(name,filename);
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

IResource * NSDevilX::NSResourceSystem::ISystemImp::createOrRetrieveResource(const String & name,const String & filename)
{
	auto ret=getResource(name);
	if(!ret)
		ret=createResource(name,filename);
	return ret;
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

CFontManager::SChar NSDevilX::NSResourceSystem::ISystemImp::getChar(ILoadedResource * resource,const CUTF8Char & c)
{
	CFontManager::SChar ret;
	if(!static_cast<IResourceImp*>(resource)->hasUserData("CFontImage"))
	{
		ret=mFontManager->get(static_cast<IResourceImp*>(resource)->getName(),c);
		if(!ret.mImage)
		{
			mFontManager->reigsterFont(static_cast<IResourceImp*>(resource)->getName(),static_cast<IResourceImp*>(resource)->getBuffer());
		}
		static_cast<IResourceImp*>(resource)->setUserData("CFontImage",ret.mImage);
	}
	ret=mFontManager->get(static_cast<IResourceImp*>(resource)->getName(),c);
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

NSRenderSystem::ITexture * NSDevilX::NSResourceSystem::ISystemImp::getRenderTexture(ILoadedResource * resource,const CUTF8Char & c)
{
	auto char_info=getChar(resource,c);
	NSRenderSystem::ITexture * ret=nullptr;
	if(static_cast<IResourceImp*>(resource)->hasUserData("NSRenderSystem::ITexture"))
	{
		ret=static_cast<IResourceImp*>(resource)->getUserData("NSRenderSystem::ITexture").get<NSRenderSystem::ITexture*>();
	}
	else
	{
		ret=NSRenderSystem::getSystem()->queryInterface_IResourceManager()->createTexture("FontTexture/"+CStringConverter::toString(char_info.mImage),NSRenderSystem::IEnum::ETextureType_2D);
		ret->queryInterface_ITexture2DWritable()->setArraySize(1);
		ret->queryInterface_ITexture2DWritable()->setFormat(NSRenderSystem::IEnum::ETexture2DFormat_A8);
		ret->queryInterface_ITexture2DWritable()->setMipmapCount(0);
		ret->queryInterface_ITexture2DWritable()->setSize(char_info.mImage->getSize().x,char_info.mImage->getSize().y);
		ret->queryInterface_ITexture2DWritable()->setPixels(char_info.mImage->getPixels(),0);
		static_cast<IResourceImp*>(resource)->setUserData("NSRenderSystem::ITexture",ret);
	}
	if(char_info.mImage->isDirty())
	{
		ret->queryInterface_ITexture2DWritable()->updatePixels(0,0);
		char_info.mImage->setDirty(False);
	}
	return ret;
}

NSRenderSystem::IGeometry * NSDevilX::NSResourceSystem::ISystemImp::getRenderGeometry(ILoadedResource * resource)
{
	return nullptr;
}
