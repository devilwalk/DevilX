#pragma once
#include "D3D11OverlayMaterial.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class COverlayMaterialManager
				:public TBaseObject<COverlayMaterialManager>
			{
			protected:
				TResourcePtrList(COverlayMaterial) mMaterials;
			public:
				COverlayMaterialManager();
				~COverlayMaterialManager();
				COverlayMaterial * getMaterial(IOverlayElementImp * element);
			};
		}
	}
}