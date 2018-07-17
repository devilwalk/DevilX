#pragma once
#include "MatchMapGrid.h"
#include "MatchTerrainChunkRenderMaterial.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CMatchTerrain2DChunk
			:public TBaseObject<CMatchTerrain2DChunk>
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_BeginRenderMaterialChange,
				EMessage_EndRenderMaterialChange
			};
		protected:
			CMatchMapGrid*const mGrid;
			CMatchTerrainChunkRenderMaterial * mRenderMaterial;
		public:
			CMatchTerrain2DChunk(CMatchMapGrid * grid);
			~CMatchTerrain2DChunk();
			CMatchMapGrid * getGrid()const
			{
				return mGrid;
			}
			Void setRenderMaterial(CMatchTerrainChunkRenderMaterial * material);
			CMatchTerrainChunkRenderMaterial * getRenderMaterial()const
			{
				return mRenderMaterial;
			}
		};
	}
}