#pragma once
#include "D3D11Pass.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CEntityTechnique;
			class CEntityPass
				:public TBaseObject<CEntityPass>
				,public CPass
				,public TMessageReceiver<IEntityRenderableImp>
				,public TMessageReceiver<IGeometryImp>
				,public TMessageReceiver<ITextureUnitStateImp>
			{
			protected:
				CEnum::EForwardPassType const mForwardType;
				CEntityTechnique * const mTechnique;
			public:
				CEntityPass(CEntityTechnique * technique);
				CEntityPass(CEnum::EForwardPassType type,CEntityTechnique * technique);
				~CEntityPass();
				CEnum::EForwardPassType getForwardType()const
				{
					return mForwardType;
				}
				CEntityTechnique * getTechnique()const
				{
					return mTechnique;
				}

				// Í¨¹ý TMessageReceiver ¼Ì³Ð
				virtual Void onMessage(IEntityRenderableImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
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