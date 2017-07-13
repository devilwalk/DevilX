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
			virtual Void shutdown()=0;
			virtual IResource * createResource(const String & name,const String & filename)=0;
			virtual IResource * getResource(const String & name)const=0;
			virtual Void destroyResource(IResource * res)=0;
			virtual IResource * createOrRetrieveResource(const String & name,const String & filename)=0;
			virtual CImage * getImage(ILoadedResource * resource)=0;
			virtual CFontManager::SChar getChar(ILoadedResource * resource,const CUTF8Char & c)=0;
			virtual NSRenderSystem::ITexture * getRenderTexture(ILoadedResource * resource)=0;
			virtual NSRenderSystem::ITexture * getRenderTexture(ILoadedResource * resource,const CUTF8Char & c)=0;
			virtual NSRenderSystem::IGeometry * getRenderGeometry(ILoadedResource * resource)=0;
		};
		ISystem * getSystem();
	}
}