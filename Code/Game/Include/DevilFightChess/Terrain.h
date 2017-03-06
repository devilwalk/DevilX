#pragma once
#include "Grid.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CTerrain
			:public TBaseObject<CTerrain>
		{
		protected:
			NSRenderSystem::IEntity * mRenderEntity;
			NSRenderSystem::IVisibleArea * mRenderVisibleArea;
			TVector<TResourcePtrVector<CGrid> > mGrids;
		public:
			CTerrain(UInt16 row,UInt16 column);
			~CTerrain();
			CGrid * getGrid(UInt16 rowIndex,UInt16 columnIndex)const
			{
				return mGrids[rowIndex][columnIndex];
			}
		};
	}
}