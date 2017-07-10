#pragma once
#include "MatchMapGrid.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CMatchScene;
		class CMatchMap
			:public TBaseObject<CMatchMap>
		{
		protected:
			CMatchScene * const mScene;
			CMatchTerrain2D * mTerrain2D;
			TVector<TResourcePtrVector<CMatchMapGrid> > mGrids;
		public:
			CMatchMap(UInt16 row,UInt16 column,CMatchScene * scene);
			~CMatchMap();
			CMatchScene * getScene()const
			{
				return mScene;
			}
			UInt16 getRowCount()const
			{
				return static_cast<UInt16>(mGrids.size());
			}
			UInt16 getColumeCount()const
			{
				if(mGrids.empty())
					return 0;
				else
					return static_cast<UInt16>(mGrids[0].size());
			}
			CMatchMapGrid * getGrid(UInt16 rowIndex,UInt16 columnIndex)const
			{
				return mGrids[columnIndex][rowIndex];
			}
		};
	}
}