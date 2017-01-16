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
			TVectorMT<TVectorMT<TVectorMT<CArea*>*>*> mAreas[2][2][2];
		public:
			ISceneImp(NSRenderSystem::IScene * renderScene=nullptr);
			~ISceneImp();
			NSRenderSystem::IScene * getRenderScene()const
			{
				return mRenderScene;
			}
			Void update();
			virtual Void setBlockMT(DirectX::FXMVECTOR positionVec,IBlock * block) override;
			virtual Void setBlockMT(const CRange3I & range,IBlock * block) override;
			virtual IBlock * getBlockMT(DirectX::FXMVECTOR positionVec) override;
		protected:
			CArea * _createOrRetrieveAreaMT(decltype(mAreas[0][0][0]) & areas,DirectX::FXMVECTOR absPositionVec,DirectX::FXMVECTOR positionVec);
			Void _setBlockToAreaMT(const CRange3I & range,IBlockImp * block);
		};
	}
}