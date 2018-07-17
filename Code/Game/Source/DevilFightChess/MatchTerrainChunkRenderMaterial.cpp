#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CMatchTerrainChunkRenderMaterial::CMatchTerrainChunkRenderMaterial(const String & name)
	:mName(name)
	,mMaterial2D(nullptr)
{}

NSDevilX::NSFightChess::CMatchTerrainChunkRenderMaterial::~CMatchTerrainChunkRenderMaterial()
{
	DEVILX_DELETE(mMaterial2D);
}
