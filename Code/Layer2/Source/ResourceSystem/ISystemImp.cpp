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
	mResourceByFileNameList.clear();
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

IResource * NSDevilX::NSResourceSystem::ISystemImp::createResource(const String & name,const String & filename,IEnum::EResourceType type)
{
	IResourceImp * res=nullptr;
	assert(!getResource(name)&&!getResourceByFileName(filename));
	switch(type)
	{
	case IEnum::EResourceType_Image:
		res=DEVILX_NEW CImageResource(name,filename);
		break;
	case IEnum::EResourceType_FBX:
		res=DEVILX_NEW CFBXResource(name,filename);
		break;
	case IEnum::EResourceType_CommonFile:
		res=DEVILX_NEW CCommonFileResource(name,filename);
		break;
	}
	if(!res)
	{
		auto ext=CDirectory::getExtensionName(filename);
		if(ext=="fbx")
			res=DEVILX_NEW CFBXResource(name,filename);
		else if((ext=="jpg")||(ext=="png")||(ext=="bmp")||(ext=="dds")||(ext=="jpeg"))
			res=DEVILX_NEW CImageResource(name,filename);
		else
			res=DEVILX_NEW CCommonFileResource(name,filename);
	}
	mResources.add(name,res);
	mResourceByFileNameList.add(filename,res);
	return res;
}

IResource * NSDevilX::NSResourceSystem::ISystemImp::getResource(const String & name) const
{
	return mResources.get(name);
}

IResource * NSDevilX::NSResourceSystem::ISystemImp::getResourceByFileName(const String & filename) const
{
	return mResourceByFileNameList.get(filename);
}

Void NSDevilX::NSResourceSystem::ISystemImp::destroyResource(IResource * res)
{
	return mResources.destroy(res->getName());
}

IResource * NSDevilX::NSResourceSystem::ISystemImp::createOrRetrieveResource(const String & name,const String & filename,IEnum::EResourceType type)
{
	auto ret=getResource(name);
	if(!ret)
	{
		auto fullname=CDirectory::getAbsolutePath(filename,CDirectory::getApplicationDirectory());
		ret=createResource(name,fullname,type);
	}
	else if(type!=IEnum::EResourceType_Unknown)
	{
		assert(type==ret->getType());
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
			CImage * ret=static_cast<CImageResource*>(resource)->getImage();
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
			if(!ISystemImp::getSingleton().mFontManager->getFace(static_cast<CCommonFileResource*>(resource)->getName()))
			{
				ISystemImp::getSingleton().mFontManager->reigsterFont(static_cast<CCommonFileResource*>(resource)->getName(),&static_cast<CCommonFileResource*>(resource)->getMemoryStream());
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
			if(!static_cast<CCommonFileResource*>(resource)->hasUserData("CFontImage"))
			{
				ret=ISystemImp::getSingleton().mFontManager->get(static_cast<CCommonFileResource*>(resource)->getName(),mChar);
				if(!ret.mImage)
				{
					ISystemImp::getSingleton().mFontManager->reigsterFont(static_cast<CCommonFileResource*>(resource)->getName(),&static_cast<CCommonFileResource*>(resource)->getMemoryStream());
				}
				static_cast<CCommonFileResource*>(resource)->setUserData("CFontImage",ret.mImage);
			}
			ret=ISystemImp::getSingleton().mFontManager->get(static_cast<CCommonFileResource*>(resource)->getName(),mChar);
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
		CImageResource * const mResource;
		IGetRenderTextureCallback * const mCallback;
		SImageCallback(CImageResource * res,IGetRenderTextureCallback * textureCallback)
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
	SImageCallback * img_callback=DEVILX_NEW SImageCallback(static_cast<CImageResource*>(resource),callback);
	getImage(resource,img_callback,sync);
}

Void NSDevilX::NSResourceSystem::ISystemImp::getRenderTexture(IResource * fontResource,const CUTF8Char & c,IGetRenderTextureCallback * callback,Bool sync)
{
	struct SCharCallback
		:public IGetCharCallback
		,public TBaseObject<SCharCallback>
	{
		CCommonFileResource * const mResource;
		IGetRenderTextureCallback * const mCallback;
		SCharCallback(CCommonFileResource * resource,IGetRenderTextureCallback * callback)
			:mResource(resource)
			,mCallback(callback)
		{}
		virtual Void onLoaded(const CFontManager::SChar & ch) override
		{
			const auto tex_name="FontTexture/"+CStringConverter::toString(ch.mImage);
			auto ret=NSRenderSystem::getSystem()->queryInterface_IResourceManager()->getTexture(tex_name);
			if(!ret)
			{
				ret=NSRenderSystem::getSystem()->queryInterface_IResourceManager()->createTexture(tex_name,NSRenderSystem::IEnum::ETextureType_2D);
				ret->queryInterface_ITexture2DWritable()->setArraySize(1);
				ret->queryInterface_ITexture2DWritable()->setFormat(NSRenderSystem::IEnum::ETexture2DFormat_A8);
				ret->queryInterface_ITexture2DWritable()->setMipmapCount(0);
				ret->queryInterface_ITexture2DWritable()->setSize(ch.mImage->getSize().x,ch.mImage->getSize().y);
				ret->queryInterface_ITexture2DWritable()->setPixels(ch.mImage->getPixels(),0);
			}
			if(ch.mImage->isDirty())
			{
				ret->queryInterface_ITexture2DWritable()->updatePixels(0,0);
				ch.mImage->setDirty(False);
			}
			mCallback->onLoaded(ret);
			DEVILX_DELETE(this);
		}
	};
	SCharCallback * char_callback=DEVILX_NEW SCharCallback(static_cast<CCommonFileResource*>(fontResource),callback);
	getChar(fontResource,c,char_callback,sync);
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
			auto processer=ISystemImp::getSingleton().mFBXResources.get(static_cast<CFBXResource*>(resource));
			if(!processer)
			{
				processer=DEVILX_NEW CFBXProcesser(static_cast<CFBXResource*>(resource));
				ISystemImp::getSingleton().mFBXResources.add(static_cast<CFBXResource*>(resource),processer);
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