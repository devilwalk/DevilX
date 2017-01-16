#pragma once
#include "IGeometryImp.h"
#include "ITextureImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IResourceManagerImp
			:public IResourceManager
			,public TBaseObject<IResourceManagerImp>
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_BeginGeometryCreate,
				EMessage_EndGeometryCreate,
				EMessage_BeginGeometryDestroy,
				EMessage_EndGeometryDestroy,
				EMessage_BeginTextureCreate,
				EMessage_EndTextureCreate,
				EMessage_BeginTextureDestroy,
				EMessage_EndTextureDestroy,
				EMessage_VertexBufferCreate,
				EMessage_VertexBufferDestroy,
				EMessage_IndexBufferCreate,
				EMessage_IndexBufferDestroy
			};
		protected:
			TNamedResourcePtrContainer<IGeometryImp> mGeometrys;
			TNamedResourcePtrContainer<ITextureImp> mTextures;
		public:
			IResourceManagerImp();
			~IResourceManagerImp();

			// Inherited via IResourceManager
			virtual IGeometry * createGeometry(const String & name) override;
			virtual Void destroyGeometry(IGeometry * geo) override;
			virtual IGeometry * getGeometry(const String & name) const override;
			virtual ITexture * createTexture(const String & name,IEnum::ETextureType type) override;
			virtual Void destroyTexture(ITexture * texture) override;
			virtual ITexture * getTexture(const String & name) const override;
		};
	}
}