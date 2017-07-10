#pragma once
#include "MatchMapGridMaterial.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CMatchMapGridMaterialManager
			:public TBaseObject<CMatchMapGridMaterialManager>
		{
		protected:
			TNamedResourcePtrMap<CMatchMapGridMaterial> mMaterials;
		public:
			CMatchMapGridMaterialManager();
			~CMatchMapGridMaterialManager();
			CMatchMapGridMaterial * getDefaultMaterial()const;
		};
	}
}