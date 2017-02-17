#pragma once
#include "ISceneImp.h"
namespace NSDevilX
{
	namespace NSCubeBlockSystem
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
			CThreadPool * mRenderableThreadPool;
			TNamedResourcePtrMap<IBlockImp> mBlocks;
			TNamedResourcePtrMap<IRenderMaterialImp> mRenderMaterials;
			TResourcePtrSet<ISceneImp> mScenes;
		public:
			ISystemImp();
			~ISystemImp();
			CThreadPool * getRenderableThreadPool()const
			{
				return mRenderableThreadPool;
			}
			virtual Void update() override;
			virtual IBlock * createBlock(const String & name) override;
			virtual IBlock * getBlock(const String & name) const override;
			virtual IScene * createScene(NSRenderSystem::IScene * renderScene=nullptr) override;
			virtual Void destroyScene(IScene * scene) override;
			virtual IRenderMaterial * createRenderMaterial(const String & name) override;
			virtual IRenderMaterial * getRenderMaterial(const String & name) const override;
			virtual Void destroyRenderMaterial(IRenderMaterial * material) override;
		};
	}
}