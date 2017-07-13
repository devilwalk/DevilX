#pragma once
#include "MatchMapGridRenderMaterial.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CMatchMapGridRenderMaterialManager
			:public TBaseObject<CMatchMapGridRenderMaterialManager>
		{
		protected:
			TNamedResourcePtrMap<CMatchMapGridRenderMaterial> mMaterials;
		public:
			CMatchMapGridRenderMaterialManager();
			~CMatchMapGridRenderMaterialManager();
			CMatchMapGridRenderMaterial * getDefaultMaterial()const;
		};
	}
}