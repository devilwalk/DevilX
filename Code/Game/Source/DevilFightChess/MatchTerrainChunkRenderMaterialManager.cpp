#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CMatchTerrainChunkRenderMaterialManager::CMatchTerrainChunkRenderMaterialManager()
{
	auto material=DEVILX_NEW CMatchTerrainChunkRenderMaterial("Internal/Default");
	material->getMaterial2D()->setColour(CFloatRGBA::sWhite);
	mMaterials.add(material->getName(),material);
}

NSDevilX::NSFightChess::CMatchTerrainChunkRenderMaterialManager::~CMatchTerrainChunkRenderMaterialManager()
{}

CMatchTerrainChunkRenderMaterial * NSDevilX::NSFightChess::CMatchTerrainChunkRenderMaterialManager::getDefaultMaterial() const
{
	return mMaterials.get("Internal/Default");
}
