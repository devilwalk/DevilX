#pragma once
#include "GL4OverlayMaterial.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGL4
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