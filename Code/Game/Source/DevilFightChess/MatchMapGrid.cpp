#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CMatchMapGrid::CMatchMapGrid(UInt16 rowIndex,UInt16 columnIndex)
	:mRowIndex(rowIndex)
	,mColumnIndex(columnIndex)
	,mRenderMaterial(nullptr)
{
}

NSDevilX::NSFightChess::CMatchMapGrid::~CMatchMapGrid()
{
}

Void NSDevilX::NSFightChess::CMatchMapGrid::setRenderMaterial(CMatchMapGridRenderMaterial * material)
{
	if(getRenderMaterial()!=material)
	{
		notify(EMessage_BeginRenderMaterialChange);
		mRenderMaterial=material;
		notify(EMessage_EndRenderMaterialChange);
	}
}
