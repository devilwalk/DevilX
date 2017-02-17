#pragma once
#include "IBlockImp.h"
namespace NSDevilX
{
	namespace NSCubeBlockSystem
	{
		class ISceneImp;
		class CArea
			:public TBaseObject<CArea>
			,public CReferenceObjectMT
		{
		public:
			const static UInt32 sBlockSize=32;
			struct SRenderable
				:public TBaseObject<SRenderable>
				,public TMessageReceiver<IRenderMaterialImp>
			{
			public:
				IRenderMaterialImp * const mMaterial;
				CArea * const mArea;
				NSRenderSystem::IEntityRenderable * mRenderable;
				TVector<UInt32> mIndicesFill;
				TVector<UInt32> mIndices;
				SRenderable(IRenderMaterialImp * material,CArea * area);
				~SRenderable();
				Void initialize();

				// Inherited via TMessageReceiver
				virtual Void onMessage(IRenderMaterialImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			};
		protected:
			static NSRenderSystem::IGeometry * sGeometry;
			const CSInt3 mPosition;
			ISceneImp * const mScene;
			TMapMT<IBlockImp*,TListMT<CRange3I*>*> mBlocks;
			NSRenderSystem::IEntity * mEntity;
			NSRenderSystem::IVisibleArea * mVisibleArea;
			TMapMT<IRenderMaterialImp*,SRenderable*> mRenderables;
			std::atomic_bool mNeedFillRenderable;
			std::atomic_bool mNeedUpdateRenderable;
		public:
			CArea(DirectX::FXMVECTOR positionVec,ISceneImp * scene);
			~CArea();
			const CSInt3 & getPosition()const
			{
				return mPosition;
			}
			ISceneImp * getScene()const
			{
				return mScene;
			}
			NSRenderSystem::IEntity * getEntity()const
			{
				return mEntity;
			}
			Void setBlockMT(DirectX::FXMVECTOR positionVec,IBlockImp * block);
			Void setBlockMT(const CRange3I & range,IBlockImp * block);
			IBlockImp * getBlockMT(DirectX::FXMVECTOR positionVec);
			Void update(Bool & needNextProcess);
		protected:
			static Boolean _fillRenderableThreadFunction(VoidPtr parameter);
			Void _initialize();
			decltype(mBlocks)::value_type::second_type _getRangesMT(IBlockImp * block);
			DirectX::XMVECTOR _getPositionInScene(DirectX::FXMVECTOR position)const;
		};
	}
}