#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CMatchMapGridRenderMaterial::CMatchMapGridRenderMaterial(const String & name)
	:mName(name)
	,mMaterial2D(nullptr)
{}

NSDevilX::NSFightChess::CMatchMapGridRenderMaterial::~CMatchMapGridRenderMaterial()
{
	DEVILX_DELETE(mMaterial2D);
}
