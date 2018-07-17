#pragma once
#include "MatchTerrainChunk2DRenderMaterial.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CMatchTerrainChunkRenderMaterial
			:public TBaseObject<CMatchTerrainChunkRenderMaterial>
		{
		protected:
			const String mName;
			CMatchTerrainChunk2DRenderMaterial * mMaterial2D;
		public:
			CMatchTerrainChunkRenderMaterial(const String & name);
			~CMatchTerrainChunkRenderMaterial();
			const String & getName()const
			{
				return mName;
			}
			CMatchTerrainChunk2DRenderMaterial * getMaterial2D()const
			{
				return mMaterial2D;
			}
		};
	}
}