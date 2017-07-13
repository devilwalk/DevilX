#pragma once
#include "MatchMapGridRenderMaterial2D.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CMatchMapGridRenderMaterial
			:public TBaseObject<CMatchMapGridRenderMaterial>
		{
		protected:
			const String mName;
			CMatchMapGridRenderMaterial2D * mMaterial2D;
		public:
			CMatchMapGridRenderMaterial(const String & name);
			~CMatchMapGridRenderMaterial();
			const String & getName()const
			{
				return mName;
			}
			CMatchMapGridRenderMaterial2D * getMaterial2D()const
			{
				return mMaterial2D;
			}
		};
	}
}