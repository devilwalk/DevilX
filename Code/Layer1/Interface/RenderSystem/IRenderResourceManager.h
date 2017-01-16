#pragma once
#include "IRenderGeometry.h"
#include "IRenderTexture.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IResourceManager
		{
		protected:
			virtual ~IResourceManager(){}
		public:
			virtual IGeometry * createGeometry(const String & name)=0;
			virtual Void destroyGeometry(IGeometry * geo)=0;
			virtual IGeometry * getGeometry(const String & name)const=0;
			virtual ITexture * createTexture(const String & name,IEnum::ETextureType type)=0;
			virtual ITexture * getTexture(const String & name)const=0;
			virtual Void destroyTexture(ITexture * texture)=0;
		};
	}
}