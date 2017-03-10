#pragma once
namespace NSDevilX
{
	namespace NSResourceSystem
	{
		class IResource;
		class ILoadRenderTextureCallback
		{
		protected:
			virtual ~ILoadRenderTextureCallback(){}
		public:
			virtual Void onLoaded(IResource * resource,NSRenderSystem::ITexture * texture)=0;
		};
		class ILoadRenderGeometryCallback
		{
		protected:
			virtual ~ILoadRenderGeometryCallback()
			{}
		public:
			virtual Void onLoaded(IResource * resource,NSRenderSystem::IGeometry * geometry)=0;
		};
		class IResource
		{
		protected:
			virtual ~IResource(){}
		public:
			virtual const String & getName()const=0;
			virtual const String & getFileName()const=0;
			virtual Void load(ILoadRenderTextureCallback * callback)=0;
			virtual Void load(ILoadRenderGeometryCallback * callback)=0;
			virtual Void unload()=0;
		};
	}
}