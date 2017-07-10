#pragma once
#include "MatchMapGridMaterial.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CMatchMapGrid
			:public TBaseObject<CMatchMapGrid>
		{
		protected:
			const UInt16 mRowIndex;
			const UInt16 mColumnIndex;
			CMatchMapGridMaterial * mMaterial;
		public:
			CMatchMapGrid(UInt16 rowIndex,UInt16 columnIndex);
			~CMatchMapGrid();
		};
	}
}