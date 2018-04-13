#pragma once
#include "IResource.h"
namespace NSDevilX
{
	namespace NSResourceSystem
	{
		class IGetImageCallback
		{
		protected:
			virtual ~IGetImageCallback(){}
		public:
			virtual Void onLoaded(CImage * img)=0;
		};
		class IGetFontFaceCallback
		{
		protected:
			virtual ~IGetFontFaceCallback(){}
		public:
			virtual Void onLoaded(CFontFace * fontFace)=0;
		};
		class IGetCharCallback
		{
		protected:
			virtual ~IGetCharCallback(){}
		public:
			virtual Void onLoaded(const CFontManager::SChar & ch)=0;
		};
		class IGetRenderTextureCallback
		{
		protected:
			virtual ~IGetRenderTextureCallback(){}
		public:
			virtual Void onLoaded(NSRenderSystem::ITexture * texture)=0;
		};
		class IGetRenderEntityCallback
		{
		protected:
			virtual ~IGetRenderEntityCallback(){}
		public:
			virtual Void onLoaded()=0;
		};
		class ISystem
		{
		protected:
			virtual ~ISystem(){}
		public:
			virtual Void update()=0;
			virtual Void shutdown()=0;
			virtual IResource * createResource(const String & name,const String & filename,IEnum::EResourceType type=IEnum::EResourceType_Unknown)=0;
			virtual IResource * getResource(const String & name)const=0;
			virtual IResource * getResourceByFileName(const String & filename)const=0;
			virtual Void destroyResource(IResource * res)=0;
			virtual IResource * createOrRetrieveResource(const String & name,const String & filename,IEnum::EResourceType type=IEnum::EResourceType_Unknown)=0;
			virtual CImage * getImage(IResource * resource)=0;
			virtual Void getImage(IResource * resource,IGetImageCallback * callback,Bool sync=False)=0;
			virtual CFontFace * getFontFace(IResource * resource)=0;
			virtual Void getFontFace(IResource * resource,IGetFontFaceCallback * callback,Bool sync=False)=0;
			virtual CFontManager::SChar getChar(IResource * resource,const CUTF8Char & c)=0;
			virtual Void getChar(IResource * resource,const CUTF8Char & c,IGetCharCallback * callback,Bool sync=False)=0;
			virtual NSRenderSystem::ITexture * getRenderTexture(IResource * resource)=0;
			virtual Void getRenderTexture(IResource * resource,IGetRenderTextureCallback * callback,Bool sync=False)=0;
			virtual NSRenderSystem::ITexture * getRenderTexture(IResource * fontResource,const CUTF8Char & c)=0;
			virtual Void getRenderTexture(IResource * fontResource,const CUTF8Char & c,IGetRenderTextureCallback * callback,Bool sync=False)=0;
			virtual NSRenderSystem::IEntity * getRenderEntity(IResource * resource,NSRenderSystem::IScene * scene)=0;
			virtual Void getRenderEntity(IResource * resource,NSRenderSystem::IEntity * entity,IGetRenderEntityCallback * callback,Bool sync=False)=0;
		};
		ISystem * getSystem();
	}
}