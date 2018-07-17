#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CMatchTerrain2DChunk::CMatchTerrain2DChunk(CMatchMapGrid * grid)
	:mGrid(grid)
	,mRenderMaterial(nullptr)
{
	mRenderMaterial=CApp::getSingleton().getGame()->getMatchMapGridRenderMaterialManager()->getDefaultMaterial();
}

NSDevilX::NSFightChess::CMatchTerrain2DChunk::~CMatchTerrain2DChunk()
{
}

Void NSDevilX::NSFightChess::CMatchTerrain2DChunk::setRenderMaterial(CMatchTerrainChunkRenderMaterial * material)
{
	if(nullptr==material)
		material=CApp::getSingleton().getGame()->getMatchMapGridRenderMaterialManager()->getDefaultMaterial();
	if(getRenderMaterial()!=material)
	{
		notify(EMessage_BeginRenderMaterialChange);
		mRenderMaterial=material;
		notify(EMessage_EndRenderMaterialChange);
	}
}
