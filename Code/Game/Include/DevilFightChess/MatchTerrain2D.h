#pragma once
#include "MatchTerrain2D.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CMatchMap;
		class CMatchTerrain2D
			:public TBaseObject<CMatchTerrain2D>
			,public TMessageReceiver<CMatchMapGrid>
		{
		protected:
			CMatchMap * const mMap;
			NSRenderSystem::IGeometry * mGeometry;
			NSRenderSystem::IEntity * mRenderEntity;
			NSRenderSystem::IVisibleArea * mRenderVisibleArea;
			TMap<CMatchMapGridRenderMaterial2D*,TList<NSRenderSystem::IEntityRenderable*> > mRenderables;
			CNameGenerator mRenderableNameGenerator;
		public:
			CMatchTerrain2D(CMatchMap * map);
			~CMatchTerrain2D();
			CMatchMap * getMap()const
			{
				return mMap;
			}
		protected:
			UInt32 _calculateVertexStart(UInt16 rowIndex,UInt16 columnIndex)const;
			UInt32 _calculateIndexStart(UInt16 rowIndex,UInt16 columnIndex)const;

			// Í¨¹ý TMessageReceiver ¼Ì³Ð
			virtual Void onMessage(CMatchMapGrid * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
		};
	}
}