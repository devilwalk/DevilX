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
				NSRenderSystem::ISubEntity * mRenderable;
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
			const CInt3 mPosition;
			ISceneImp * const mScene;
			TMapMT<IBlockImp*,TListMT<CRange3I*>*> mBlocks;
			NSRenderSystem::IEntity * mEntity;
			NSRenderSystem::IVisibleArea * mVisibleArea;
			TMapMT<IRenderMaterialImp*,SRenderable*> mRenderables;
			std::atomic_bool mNeedFillRenderable;
			std::atomic_bool mNeedUpdateRenderable;
		public:
			CArea(const CInt3 & position,ISceneImp * scene);
			~CArea();
			const CInt3 & getPosition()const
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
			Void setBlockMT(const CInt3 & position,IBlockImp * block);
			Void setBlockMT(const CRange3I & range,IBlockImp * block);
			IBlockImp * getBlockMT(const CInt3 & position);
			Void update(Bool & needNextProcess);
		protected:
			static Boolean _fillRenderableThreadFunction(VoidPtr parameter);
			Void _initialize();
			decltype(mBlocks)::value_type::second_type _getRangesMT(IBlockImp * block);
			DirectX::XMVECTOR _getPositionInScene(DirectX::FXMVECTOR position)const;
		};
	}
}