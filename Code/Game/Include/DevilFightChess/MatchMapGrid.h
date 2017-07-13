#pragma once
#include "MatchMapGridRenderMaterial.h"
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
				EMessage_BeginRenderMaterialChange,
				EMessage_EndRenderMaterialChange
			};
		protected:
			const UInt16 mRowIndex;
			const UInt16 mColumnIndex;
			CMatchMapGridRenderMaterial * mRenderMaterial;
		public:
			CMatchMapGrid(UInt16 rowIndex,UInt16 columnIndex);
			~CMatchMapGrid();
			UInt16 getRowIndex()const
			{
				return mRowIndex;
			}
			UInt16 getColumeIndex()const
			{
				return mColumnIndex;
			}
			Void setRenderMaterial(CMatchMapGridRenderMaterial * material);
			CMatchMapGridRenderMaterial * getRenderMaterial()const
			{
				return mRenderMaterial;
			}
		};
	}
}