#pragma once
#include "IResourceImp.h"
#include "FBXProcesser.h"
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
			TResourcePtrMap<IResourceImp*,CFBXProcesser> mFBXResources;
		public:
			ISystemImp();
			~ISystemImp();
			CThreadPool * getIOPool()const
			{
				return mIOPool;
			}

			// 通过 ISystem 继承
			virtual Void update() override;
			virtual Void shutdown() override;
			virtual IResource * createResource(const String & name,const String & filename) override;
			virtual IResource * getResource(const String & name) const override;
			virtual Void destroyResource(IResource * res) override;
			virtual IResource * createOrRetrieveResource(const String & name,const String & filename) override;
			virtual Void getImage(IResource * resource,IGetImageCallback * callback,Bool sync) override;
			virtual Void getFontFace(IResource * resource,IGetFontFaceCallback * callback,Bool sync) override;
			virtual Void getChar(IResource * resource,const CUTF8Char & c,IGetCharCallback * callback,Bool sync) override;
			virtual Void getRenderTexture(IResource * resource,IGetRenderTextureCallback * callback,Bool sync) override;
			virtual Void getRenderTexture(IResource * resource,const CUTF8Char & c,IGetRenderTextureCallback * callback,Bool sync) override;
			virtual NSRenderSystem::IEntity * getRenderEntity(IResource * resource,NSRenderSystem::IScene * scene) override;
			virtual Void getRenderEntity(IResource * resource,NSRenderSystem::IEntity * entity,IGetRenderEntityCallback * callback,Bool sync) override;

			// 通过 ISystem 继承
			virtual CImage * getImage(IResource * resource) override;
			virtual CFontFace * getFontFace(IResource * resource) override;
			virtual CFontManager::SChar getChar(IResource * resource,const CUTF8Char & c) override;
			virtual NSRenderSystem::ITexture * getRenderTexture(IResource * resource) override;
			virtual NSRenderSystem::ITexture * getRenderTexture(IResource * resource,const CUTF8Char & c) override;
		};
	}
}