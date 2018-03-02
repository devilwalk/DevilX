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
		class IGetRenderGeometryCallback
		{
		protected:
			virtual ~IGetRenderGeometryCallback(){}
		public:
			virtual Void onLoaded(NSRenderSystem::IGeometry * geometry)=0;
		};
		class ISystem
		{
		protected:
			virtual ~ISystem(){}
		public:
			virtual Void update()=0;
			virtual Void shutdown()=0;
			virtual IResource * createResource(const String & name,const String & filename)=0;
			virtual IResource * getResource(const String & name)const=0;
			virtual Void destroyResource(IResource * res)=0;
			virtual IResource * createOrRetrieveResource(const String & name,const String & filename)=0;
			virtual CImage * getImage(IResource * resource)=0;
			virtual Void getImage(IResource * resource,IGetImageCallback * callback,Bool sync=False)=0;
			virtual CFontFace * getFontFace(IResource * resource)=0;
			virtual Void getFontFace(IResource * resource,IGetFontFaceCallback * callback,Bool sync=False)=0;
			virtual CFontManager::SChar getChar(IResource * resource,const CUTF8Char & c)=0;
			virtual Void getChar(IResource * resource,const CUTF8Char & c,IGetCharCallback * callback,Bool sync=False)=0;
			virtual NSRenderSystem::ITexture * getRenderTexture(IResource * resource)=0;
			virtual Void getRenderTexture(IResource * resource,IGetRenderTextureCallback * callback,Bool sync=False)=0;
			virtual NSRenderSystem::ITexture * getRenderTexture(IResource * resource,const CUTF8Char & c)=0;
			virtual Void getRenderTexture(IResource * resource,const CUTF8Char & c,IGetRenderTextureCallback * callback,Bool sync=False)=0;
			virtual NSRenderSystem::IGeometry * getRenderGeometry(IResource * resource)=0;
			virtual Void getRenderGeometry(IResource * resource,IGetRenderGeometryCallback * callback,Bool sync=False)=0;
		};
		ISystem * getSystem();
	}
}