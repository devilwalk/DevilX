#pragma once
#include "Area.h"
namespace NSDevilX
{
	namespace NSCubeBlockSystem
	{
		class ISceneImp
			:public TBaseObject<ISceneImp>
			,public IScene
			,public CMessageNotifier
		{
		protected:
			NSRenderSystem::IScene * mRenderScene;
			const Bool mSelfRenderScene;
			C3DTreeContainer mAreas;
		public:
			ISceneImp(NSRenderSystem::IScene * renderScene=nullptr);
			~ISceneImp();
			NSRenderSystem::IScene * getRenderScene()const
			{
				return mRenderScene;
			}
			Void update();
			virtual Void setBlock(const CInt3 & position,IBlock * block) override;
			virtual Void setBlock(const CRange3I & range,IBlock * block) override;
			virtual IBlock * getBlock(const CInt3 & position) const override;
		};
	}
}