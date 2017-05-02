#pragma once
namespace NSDevilX
{
	namespace NSResourceSystem
	{
		class ISystemImp
			:public TBaseObject<ISystemImp>
			,public ISystem
			,public TSingletonEx<ISystemImp>
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_Update
			};
		protected:
			CThreadPool * mIOPool;
			CFontManager * mFontManager;
			TNamedResourcePtrMap<IResourceImp> mResources;
		public:
			ISystemImp();
			~ISystemImp();
			CThreadPool * getIOPool()const
			{
				return mIOPool;
			}

			// ͨ�� ISystem �̳�
			virtual Void update() override;
			virtual Void shutdown() override;
			virtual IResource * createResource(const String & name,const String & fileName) override;
			virtual IResource * getResource(const String & name) const override;
			virtual Void destroyResource(IResource * res) override;
			virtual CImage * getImage(ILoadedResource * resource) override;
			virtual CFontManager::SChar getChar(ILoadedResource * resource,const CUTF8Char & c) override;
			virtual NSRenderSystem::ITexture * getRenderTexture(ILoadedResource * resource) override;
			virtual NSRenderSystem::ITexture * getRenderTexture(ILoadedResource * resource,const CUTF8Char & c) override;
			virtual NSRenderSystem::IGeometry * getRenderGeometry(ILoadedResource * resource) override;
		};
	}
}