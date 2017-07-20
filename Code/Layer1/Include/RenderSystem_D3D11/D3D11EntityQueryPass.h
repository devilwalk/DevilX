#pragma once
#include "D3D11EntityPass.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CEntityTechnique;
			class CEntityQueryPass
				:public TBaseObject<CEntityQueryPass>
				,public CEntityPass
			{
			protected:
			public:
				CEntityQueryPass(CEntityTechnique * technique);
				~CEntityQueryPass();
			protected:
				Void _updateShader();
				Void _updateRasterizerState();
				Void _updateBlendState();
				Void _updateDepthStencilState();
				Void _updateSamplerState();
				virtual Void onMessage(ISubEntityImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				virtual Void onMessage(ITextureUnitStateImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				virtual Void onMessage(IGeometryImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			};
		}
	}
}