#pragma once
#include "D3D11Pass.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
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
			};
		}
	}
}