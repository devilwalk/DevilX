#pragma once
#include "GL4Pass.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGL4
		{
			class COverlayMaterial
				:public TBaseObject<COverlayMaterial>
				,public CPass
			{
			protected:
			public:
				COverlayMaterial(CTexture * texture);
				~COverlayMaterial();
			protected:
				Void _updateShader();
				Void _updateRasterizerState();
				Void _updateBlendState();
				Void _updateDepthStencilState();
				Void _updateSamplerState();
			};
		}
	}
}