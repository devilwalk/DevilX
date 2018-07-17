#pragma once
#include "MatchTerrainChunkRenderMaterial.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CMatchTerrainChunkRenderMaterialManager
			:public TBaseObject<CMatchTerrainChunkRenderMaterialManager>
		{
		protected:
			TNamedResourcePtrMap<CMatchTerrainChunkRenderMaterial> mMaterials;
		public:
			CMatchTerrainChunkRenderMaterialManager();
			~CMatchTerrainChunkRenderMaterialManager();
			CMatchTerrainChunkRenderMaterial * getDefaultMaterial()const;
		};
	}
}