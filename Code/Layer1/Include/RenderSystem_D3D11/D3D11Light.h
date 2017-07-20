#pragma once
#include "D3D11BaseObject.h"
#include "D3D11ConstantBufferContainer.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CSceneImp;
			class CLight
				:public TInterfaceObject<ILightImp>
				,public TBaseObject<CLight>
				,public CConstantBufferContainer
				,public TMessageReceiver<IColourUnitStateImp>
			{
			protected:
				CSceneImp * const mScene;
			public:
				CLight(ILightImp * interfaceImp);
				~CLight();
				CSceneImp * getScene()const
				{
					return mScene;
				}

				// Inherited via TInterfaceObject
				virtual Void onMessage(ILightImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				virtual Void onMessage(IColourUnitStateImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				// Inherited via CConstantBufferContainer
				virtual Void _updateConstantBuffer(Byte * buffer) override;
			};
		}
	}
}