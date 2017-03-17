#pragma once
#include "IResource.h"
namespace NSDevilX
{
	namespace NSResourceSystem
	{
		class ISystem
		{
		protected:
			virtual ~ISystem(){}
		public:
			virtual Void update()=0;
			virtual IResource * createResource(const String & name,const String & fileName)=0;
			virtual IResource * getResource(const String & name)const=0;
			virtual Void destroyResource(IResource * res)=0;
			virtual CImage * getImage(ILoadedResource * resource)=0;
			virtual CFontImage * getFontImage(ILoadedResource * resource,const CUTF8Char & c,CFloat2 * pixelStart,CFloat2 pixelEnd)=0;
			virtual NSRenderSystem::ITexture * getRenderTexture(ILoadedResource * resource)=0;
			virtual NSRenderSystem::ITexture * getRenderTexture(ILoadedResource * resource,const CUTF8Char & c,CFloat2 * pixelStart,CFloat2 pixelEnd)=0;
			virtual NSRenderSystem::IGeometry * getRenderGeometry(ILoadedResource * resource)=0;
		};
		ISystem * getSystem();
	}
}