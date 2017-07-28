#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CMatchMap::CMatchMap(UInt16 row,UInt16 column,CMatchScene * scene)
	:mScene(scene)
{
	mGrids.resize(column);
	for(UInt16 colume_index=0;colume_index<column;++colume_index)
	{
		mGrids[colume_index].reserve(row);
		for(UInt16 row_index=0;row_index<row;++row_index)
		{
			auto grid=DEVILX_NEW CMatchMapGrid(row_index,colume_index);
			mGrids[colume_index].push_back(grid);
		}
	}
}

NSDevilX::NSFightChess::CMatchMap::~CMatchMap()
{}