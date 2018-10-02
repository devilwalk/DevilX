#pragma once
#include "IGeometryImp.h"
#include "ITextureImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		template<class TInterface>
		class TResource
			:public TInterface
			,public CReferenceObject
		{
		protected:
			String mName;
		public:
			Void setName(const String & name)
			{
				mName=name;
			}
			virtual const String & getName() const override final
			{
				return mName;
			}
		protected:
			virtual ~TResource()
			{
			}
		};
		typedef TResource<IBuffer> IBufferImp;
		typedef TResource<IShader> IShaderImp;
		typedef TResource<IProgram> IProgramImp;
		typedef TResource<ISamplerState> ISamplerStateImp;
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
				EMessage_BeginBufferDestroy,
				EMessage_EndBufferDestroy,
				EMessage_CreateBuffer,
				EMessage_CreateShader,
				EMessage_CreateProgram,
				EMessage_CreateSamplerState
			};
		protected:
			TNamedRefResourcePtrMap(IGeometryImp) mGeometrys;
			TNamedRefResourcePtrMap(ITextureImp) mTextures;
			TNamedRefResourcePtrMap(IBufferImp) mBuffers;
			TRefResourcePtrSet(IBufferImp) mInternalBuffers;
			TNamedRefResourcePtrMap(IShaderImp) mShaders;
			TNamedRefResourcePtrMap(IProgramImp) mPrograms;
			TNamedRefResourcePtrMap(ISamplerStateImp) mSamplerStates;
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

			// 通过 IResourceManager 继承
			virtual IShader * createShader(const String & name) override;
			virtual IShader * getShader(const String & name) const override;
			virtual Void destroyShader(IShader * shader) override;
			virtual IProgram * createProgram(const String & name) override;
			virtual IProgram * getProgram(const String & name) const override;
			virtual Void destroyProgram(IProgram * program) override;
			virtual IMaterial * createMaterial(const String & name) override;
			virtual IMaterial * getMaterial() const override;
			virtual Void destroyMaterial(IMaterial * material) override;

			// 通过 IResourceManager 继承
			virtual ISamplerState * createSamplerState(const String & name) override;
			virtual ISamplerState * getSamplerState(const String & name) const override;
			virtual Void destroySamplerState(const String & name) override;
		};
	}
}