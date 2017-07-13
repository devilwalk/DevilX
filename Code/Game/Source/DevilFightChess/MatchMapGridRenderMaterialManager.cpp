#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CMatchMapGridRenderMaterialManager::CMatchMapGridRenderMaterialManager()
{
	auto material=DEVILX_NEW CMatchMapGridRenderMaterial("Internal/Default");
	material->getMaterial2D()->setColour(CFloatRGBA::sWhite);
	mMaterials.add(material->getName(),material);
}

NSDevilX::NSFightChess::CMatchMapGridRenderMaterialManager::~CMatchMapGridRenderMaterialManager()
{}

CMatchMapGridRenderMaterial * NSDevilX::NSFightChess::CMatchMapGridRenderMaterialManager::getDefaultMaterial() const
{
	return mMaterials.get("Internal/Default");
}
