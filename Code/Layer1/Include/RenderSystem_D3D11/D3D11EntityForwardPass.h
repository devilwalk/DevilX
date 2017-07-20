#pragma once
#include "D3D11EntityPass.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CEntityTechnique;
			class CEntityForwardPass
				:public TBaseObject<CEntityForwardPass>
				,public CEntityPass
			{
			protected:
				CEnum::EForwardPassType const mForwardType;
			public:
				CEntityForwardPass(CEntityTechnique * technique);
				CEntityForwardPass(CEnum::EForwardPassType type,CEntityTechnique * technique);
				~CEntityForwardPass();
				CEnum::EForwardPassType getForwardType()const
				{
					return mForwardType;
				}

				// Í¨¹ý TMessageReceiver ¼Ì³Ð
				virtual Void onMessage(ISubEntityImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				virtual Void onMessage(IGeometryImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				virtual Void onMessage(ITextureUnitStateImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			protected:
				Void _updateShader();
				Void _updateTextures();
				Void _updateRasterizerState();
				Void _updateBlendState();
				Void _updateDepthStencilState();
				Void _registerToIGeometryImp();
				Void _unregisterToIGeometryImp();
			};
		}
	}
}