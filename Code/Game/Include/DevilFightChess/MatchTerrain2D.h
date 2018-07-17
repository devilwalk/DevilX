#pragma once
#include "MatchTerrain2DChunk.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CMatchMap;
		class CMatchTerrain2D
			:public TBaseObject<CMatchTerrain2D>
			,public TMessageReceiver<CMatchTerrain2DChunk>
		{
		protected:
			CMatchMap * const mMap;
			NSRenderSystem::IGeometry * mGeometry;
			NSRenderSystem::IEntity * mRenderEntity;
			NSRenderSystem::IVisibleArea * mRenderVisibleArea;
			NSRenderSystem::IBuffer * mQueryBuffer;
			TMap<CMatchTerrain2DChunkRenderMaterial*,TList<NSRenderSystem::ISubEntity*> > mSubEntities;
			CNameGenerator mRenderableNameGenerator;
		public:
			CMatchTerrain2D(CMatchMap * map);
			~CMatchTerrain2D();
			CMatchMap * getMap()const
			{
				return mMap;
			}
		protected:
			UInt32 _calculateIndexStart(UInt16 rowIndex,UInt16 columnIndex)const;

			// Í¨¹ý TMessageReceiver ¼Ì³Ð
			virtual Void onMessage(CMatchTerrain2DChunk * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
		};
	}
}