#pragma once
#include "IGeometryImp.h"
#include "ITextureImp.h"
#include "IBufferImp.h"
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
				EMessage_BeginBufferCreate,
				EMessage_EndBufferCreate,
				EMessage_BeginBufferDestroy,
				EMessage_EndBufferDestroy,
				EMessage_VertexBufferCreate,
				EMessage_VertexBufferDestroy,
				EMessage_IndexBufferCreate,
				EMessage_IndexBufferDestroy
			};
		protected:
			TNamedRefResourcePtrMap(IGeometryImp) mGeometrys;
			TNamedRefResourcePtrMap(ITextureImp) mTextures;
			TNamedRefResourcePtrMap(IBufferImp) mBuffers;
			TRefResourcePtrSet(IBufferImp) mInternalBuffers;
			CNameGenerator mInternalBufferNameGenerator;
		public:
			IResourceManagerImp();
			~IResourceManagerImp();
			IBufferImp * createVertexBuffer()
			{
				notify(EMessage_BeginBufferCreate);
				auto ret=DEVILX_NEW IBufferImp(mInternalBufferNameGenerator.generateNext());
				mInternalBuffers.insert(ret);
				notify(EMessage_EndBufferCreate,ret);
				return ret;
			}
			IBufferImp * createIndexBuffer()
			{
				notify(EMessage_BeginBufferCreate);
				auto ret=DEVILX_NEW IBufferImp(mInternalBufferNameGenerator.generateNext(),IBufferImp::EType_IndexBuffer);
				mInternalBuffers.insert(ret);
				notify(EMessage_EndBufferCreate,ret);
				return ret;
			}
			Void destroyInternalBuffer(IBufferImp * buffer)
			{
				notify(EMessage_BeginBufferDestroy,buffer);
				mInternalBuffers.destroy(buffer);
				notify(EMessage_EndBufferDestroy);
			}
			// Inherited via IResourceManager
			virtual IGeometry * createGeometry(const String & name) override;
			virtual Void destroyGeometry(IGeometry * geo) override;
			virtual IGeometry * getGeometry(const String & name) const override;
			virtual ITexture * createTexture(const String & name,IEnum::ETextureType type) override;
			virtual Void destroyTexture(ITexture * texture) override;
			virtual ITexture * getTexture(const String & name) const override;
			virtual IBuffer * createBuffer(const String & name) override;
			virtual IBuffer * getBuffer(const String & name) const override;
			virtual Void destroyBuffer(IBuffer * buffer) override;
		};
	}
}