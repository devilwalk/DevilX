#pragma once
#include "Grid.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CTerrain
		{
		protected:
			TVector<TResourcePtrVector<CGrid> > mGrids;
		public:
			CTerrain(UInt16 row,UInt16 column);
			~CTerrain();
			CGrid * getGrid(UInt16 rowIndex,UInt16 column)const;
		};
	}
}