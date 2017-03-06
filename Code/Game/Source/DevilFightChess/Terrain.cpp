#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CTerrain::CTerrain(UInt16 row,UInt16 column)
	:mRenderEntity(nullptr)
	,mRenderVisibleArea(nullptr)
{
	mGrids.resize(row);
	for(UInt16 i=0;i<row;++i)
	{
		mGrids[i].resize(column);
		for(UInt16 j=0;j<column;++j)
		{
			mGrids[i][j]=DEVILX_NEW CGrid(i,j);
		}
	}
}

NSDevilX::NSFightChess::CTerrain::~CTerrain()
{}
