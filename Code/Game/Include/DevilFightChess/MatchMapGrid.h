#pragma once
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CMatchMapGrid
			:public TBaseObject<CMatchMapGrid>
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
			};
		protected:
			const UInt8 mRowIndex;
			const UInt8 mColumnIndex;
		public:
			CMatchMapGrid(UInt8 rowIndex,UInt8 columnIndex);
			~CMatchMapGrid();
			UInt8 getRowIndex()const
			{
				return mRowIndex;
			}
			UInt8 getColumeIndex()const
			{
				return mColumnIndex;
			}
		};
	}
}