#pragma once
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CGrid
			:public TBaseObject<CGrid>
		{
		protected:
			const UInt16 mRowIndex;
			const UInt16 mColumnIndex;
		public:
			CGrid(UInt16 rowIndex,UInt16 columnIndex);
			~CGrid();
		};
	}
}