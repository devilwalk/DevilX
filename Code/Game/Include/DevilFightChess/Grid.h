#pragma once
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CGrid
			:public TBaseObject<CGrid>
		{
		protected:
			UInt16 mRowIndex;
			UInt16 mColumnIndex;
		public:
			CGrid(UInt16 rowIndex,UInt16 columnIndex);
			~CGrid();
		};
	}
}