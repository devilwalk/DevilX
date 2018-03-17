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
	{
		auto fullname=CDirectory::getAbsolutePath(filename,CDirectory::getApplicationDirectory());
		ret=createResource(name,fullname);
	}
	return ret;
}

Void NSDevilX::NSResourceSystem::ISystemImp::getImage(IResource * resource,IGetImageCallback * callback,Bool sync=False)
{
	struct SLoadCallback
		:public ILoadCallback
		,public TBaseObject<SLoadCallback>
	{
		IGetImageCallback * const mCallback;
		SLoadCallback(IGetImageCallback * retCallback)
			:mCallback(retCallback)
		{}
		virtual Void onLoaded(IResource * resource) override
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
			mCallback->onLoaded(ret);
			DEVILX_DELETE(this);
		}
	};
	auto load_callback=DEVILX_NEW SLoadCallback(callback);
	resource->load(load_callback,sync);
}

Void NSDevilX::NSResourceSystem::ISystemImp::getFontFace(IResource * resource,IGetFontFaceCallback * callback,Bool sync)
{
	struct SLoadCallback
		:public ILoadCallback
		,public TBaseObject<SLoadCallback>
	{
		IGetFontFaceCallback * const mCallback;
		SLoadCallback(IGetFontFaceCallback * retCallback)
			:mCallback(retCallback)
		{}
		virtual Void onLoaded(IResource * resource) override
		{
			if(!ISystemImp::getSingleton().mFontManager->getFace(static_cast<IResourceImp*>(resource)->getName()))
			{
				ISystemImp::getSingleton().mFontManager->reigsterFont(static_cast<IResourceImp*>(resource)->getName(),static_cast<IResourceImp*>(resource)->getBuffer());
			}
			mCallback->onLoaded(ISystemImp::getSingleton().mFontManager->getFace(static_cast<IResourceImp*>(resource)->getName()));
			DEVILX_DELETE(this);
		}
	};
	auto load_callback=DEVILX_NEW SLoadCallback(callback);
	resource->load(load_callback,sync);
}

Void NSDevilX::NSResourceSystem::ISystemImp::getChar(IResource * resource,const CUTF8Char & c,IGetCharCallback * callback,Bool sync)
{
	struct SLoadCallback
		:public ILoadCallback
		,public TBaseObject<SLoadCallback>
	{
		IGetCharCallback * const mCallback;
		const CUTF8Char mChar;
		SLoadCallback(IGetCharCallback * retCallback,const CUTF8Char & ch)
			:mCallback(retCallback)
			,mChar(ch)
		{}
		virtual Void onLoaded(IResource * resource) override
		{
			CFontManager::SChar ret;
			if(!static_cast<IResourceImp*>(resource)->hasUserData("CFontImage"))
			{
				ret=ISystemImp::getSingleton().mFontManager->get(static_cast<IResourceImp*>(resource)->getName(),mChar);
				if(!ret.mImage)
				{
					ISystemImp::getSingleton().mFontManager->reigsterFont(static_cast<IResourceImp*>(resource)->getName(),static_cast<IResourceImp*>(resource)->getBuffer());
				}
				static_cast<IResourceImp*>(resource)->setUserData("CFontImage",ret.mImage);
			}
			ret=ISystemImp::getSingleton().mFontManager->get(static_cast<IResourceImp*>(resource)->getName(),mChar);
			mCallback->onLoaded(ret);
			DEVILX_DELETE(this);
		}
	};
	auto load_callback=DEVILX_NEW SLoadCallback(callback,c);
	resource->load(load_callback,sync);
}

Void NSDevilX::NSResourceSystem::ISystemImp::getRenderTexture(IResource * resource,IGetRenderTextureCallback * callback,Bool sync)
{
	struct SImageCallback
		:public IGetImageCallback
		,public TBaseObject<SImageCallback>
	{
		IResourceImp * const mResource;
		IGetRenderTextureCallback * const mCallback;
		SImageCallback(IResourceImp * res,IGetRenderTextureCallback * textureCallback)
			:mResource(res)
			,mCallback(textureCallback)
		{}
		virtual Void onLoaded(CImage * img) override
		{
			NSRenderSystem::ITexture * ret=nullptr;
			if(mResource->hasUserData("NSRenderSystem::ITexture"))
			{
				ret=mResource->getUserData("NSRenderSystem::ITexture").get<NSRenderSystem::ITexture*>();
			}
			else
			{
				ret=NSRenderSystem::getSystem()->queryInterface_IResourceManager()->createTexture(mResource->getFileName(),NSRenderSystem::IEnum::ETextureType_2D);
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
				mResource->setUserData("NSRenderSystem::ITexture",ret);
			}
			mCallback->onLoaded(ret);
			DEVILX_DELETE(this);
		}
	};
	SImageCallback * img_callback=DEVILX_NEW SImageCallback(static_cast<IResourceImp*>(resource),callback);
	getImage(resource,img_callback,sync);
}

Void NSDevilX::NSResourceSystem::ISystemImp::getRenderTexture(IResource * resource,const CUTF8Char & c,IGetRenderTextureCallback * callback,Bool sync)
{
	struct SImageCallback
		:public IGetImageCallback
		,public TBaseObject<SImageCallback>
	{
		IResourceImp * const mResource;
		CFontManager::SChar mCharInfo;
		IGetRenderTextureCallback * const mCallback;
		SImageCallback(IResourceImp * res,const CFontManager::SChar & ch,IGetRenderTextureCallback * textureCallback)
			:mResource(res)
			,mCharInfo(ch)
			,mCallback(textureCallback)
		{}
		virtual Void onLoaded(CImage * img) override
		{
			NSRenderSystem::ITexture * ret=nullptr;
			if(mResource->hasUserData("NSRenderSystem::ITexture"))
			{
				ret=mResource->getUserData("NSRenderSystem::ITexture").get<NSRenderSystem::ITexture*>();
			}
			else
			{
				ret=NSRenderSystem::getSystem()->queryInterface_IResourceManager()->createTexture("FontTexture/"+CStringConverter::toString(mCharInfo.mImage),NSRenderSystem::IEnum::ETextureType_2D);
				ret->queryInterface_ITexture2DWritable()->setArraySize(1);
				ret->queryInterface_ITexture2DWritable()->setFormat(NSRenderSystem::IEnum::ETexture2DFormat_A8);
				ret->queryInterface_ITexture2DWritable()->setMipmapCount(0);
				ret->queryInterface_ITexture2DWritable()->setSize(mCharInfo.mImage->getSize().x,mCharInfo.mImage->getSize().y);
				ret->queryInterface_ITexture2DWritable()->setPixels(mCharInfo.mImage->getPixels(),0);
				mResource->setUserData("NSRenderSystem::ITexture",ret);
			}
			if(mCharInfo.mImage->isDirty())
			{
				ret->queryInterface_ITexture2DWritable()->updatePixels(0,0);
				mCharInfo.mImage->setDirty(False);
			}
			mCallback->onLoaded(ret);
			DEVILX_DELETE(this);
		}
	};
	struct SCharCallback
		:public IGetCharCallback
		,public TBaseObject<SCharCallback>
	{
		IResourceImp * const mResource;
		IGetRenderTextureCallback * const mCallback;
		const Bool mSync;
		SCharCallback(IResourceImp * resource,IGetRenderTextureCallback * callback,Bool sync)
			:mResource(resource)
			,mCallback(callback)
			,mSync(sync)
		{}
		virtual Void onLoaded(const CFontManager::SChar & ch) override
		{
			SImageCallback * img_callback=DEVILX_NEW SImageCallback(mResource,ch,mCallback);
			ISystemImp::getSingleton().getImage(mResource,img_callback,mSync);
			DEVILX_DELETE(this);
		}
	};
	SCharCallback * char_callback=DEVILX_NEW SCharCallback(static_cast<IResourceImp*>(resource),callback,sync);
	getChar(resource,c,char_callback,sync);
}

NSRenderSystem::IEntity * NSDevilX::NSResourceSystem::ISystemImp::getRenderEntity(IResource * resource,NSRenderSystem::IScene * scene)
{
	NSRenderSystem::IEntity * ret=scene->createEntity(resource->getName());
	getRenderEntity(resource,ret,nullptr,True);
	return ret;
}

Void NSDevilX::NSResourceSystem::ISystemImp::getRenderEntity(IResource * resource,NSRenderSystem::IEntity * entity,IGetRenderEntityCallback * callback,Bool sync)
{
	struct SLoadCallback
		:public ILoadCallback
		,public TBaseObject<SLoadCallback>
	{
		IGetRenderEntityCallback * const mCallback;
		NSRenderSystem::IEntity * const mEntity;
		SLoadCallback(IGetRenderEntityCallback * retCallback,NSRenderSystem::IEntity * entity)
			:mCallback(retCallback)
			,mEntity(entity)
		{}
		virtual Void onLoaded(IResource * resource) override
		{
			auto processer=ISystemImp::getSingleton().mFBXResources.get(static_cast<IResourceImp*>(resource));
			if(!processer)
			{
				processer=DEVILX_NEW CFBXProcesser(static_cast<IResourceImp*>(resource));
				ISystemImp::getSingleton().mFBXResources.add(static_cast<IResourceImp*>(resource),processer);
			}
			processer->process(mEntity);
			if(mCallback)
				mCallback->onLoaded();
			DEVILX_DELETE(this);
		}
	};
	auto load_callback=DEVILX_NEW SLoadCallback(callback,entity);
	resource->load(load_callback,sync);
}

CImage * NSDevilX::NSResourceSystem::ISystemImp::getImage(IResource * resource)
{
	CImage * ret=nullptr;
	struct SImageCallback
		:public IGetImageCallback
		,public TBaseObject<SImageCallback>
	{
		CImage * & mRef;
		SImageCallback(CImage * & ref)
			:mRef(ref)
		{}
		virtual Void onLoaded(CImage * img) override
		{
			mRef=img;
		}
	};
	SImageCallback callback(ret);
	getImage(resource,&callback,True);
	return ret;
}

CFontFace * NSDevilX::NSResourceSystem::ISystemImp::getFontFace(IResource * resource)
{
	CFontFace * ret=nullptr;
	struct SFontFaceCallback
		:public IGetFontFaceCallback
		,public TBaseObject<SFontFaceCallback>
	{
		CFontFace * & mRef;
		SFontFaceCallback(CFontFace * & ref)
			:mRef(ref)
		{}
		virtual Void onLoaded(CFontFace * face) override
		{
			mRef=face;
		}
	};
	SFontFaceCallback callback(ret);
	getFontFace(resource,&callback,True);
	return ret;
}

CFontManager::SChar NSDevilX::NSResourceSystem::ISystemImp::getChar(IResource * resource,const CUTF8Char & c)
{
	CFontManager::SChar ret;
	struct SCharCallback
		:public IGetCharCallback
		,public TBaseObject<SCharCallback>
	{
		CFontManager::SChar & mRef;
		SCharCallback(CFontManager::SChar & ref)
			:mRef(ref)
		{}
		virtual Void onLoaded(const CFontManager::SChar & c) override
		{
			mRef=c;
		}
	};
	SCharCallback callback(ret);
	getChar(resource,c,&callback,True);
	return ret;
}

NSRenderSystem::ITexture * NSDevilX::NSResourceSystem::ISystemImp::getRenderTexture(IResource * resource)
{
	NSRenderSystem::ITexture * ret=nullptr;
	struct STextureCallback
		:public IGetRenderTextureCallback
		,public TBaseObject<STextureCallback>
	{
		NSRenderSystem::ITexture * & mRef;
		STextureCallback(NSRenderSystem::ITexture * & ref)
			:mRef(ref)
		{}
		virtual Void onLoaded(NSRenderSystem::ITexture * tex) override
		{
			mRef=tex;
		}
	};
	STextureCallback callback(ret);
	getRenderTexture(resource,&callback,True);
	return ret;
}

NSRenderSystem::ITexture * NSDevilX::NSResourceSystem::ISystemImp::getRenderTexture(IResource * resource,const CUTF8Char & c)
{
	NSRenderSystem::ITexture * ret=nullptr;
	struct STextureCallback
		:public IGetRenderTextureCallback
		,public TBaseObject<STextureCallback>
	{
		NSRenderSystem::ITexture * & mRef;
		STextureCallback(NSRenderSystem::ITexture * & ref)
			:mRef(ref)
		{}
		virtual Void onLoaded(NSRenderSystem::ITexture * tex) override
		{
			mRef=tex;
		}
	};
	STextureCallback callback(ret);
	getRenderTexture(resource,c,&callback,True);
	return ret;
}