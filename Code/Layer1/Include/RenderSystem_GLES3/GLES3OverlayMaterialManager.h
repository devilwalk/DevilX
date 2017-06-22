#pragma once
#include "GLES3OverlayMaterial.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGLES3
		{
			class COverlayMaterialManager
				:public TBaseObject<COverlayMaterialManager>
			{
			protected:
				TResourcePtrList<COverlayMaterial> mMaterials;
			public:
				COverlayMaterialManager();
				~COverlayMaterialManager();
				COverlayMaterial * getMaterial(IOverlayElementImp * element);
			};
		}
	}
}