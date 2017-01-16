#pragma once
#include "D3D11BaseObject.h"
#include "D3D11ConstantBufferContainer.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CScene;
			class CLight
				:public TInterfaceObject<ILightImp>
				,public TBaseObject<CLight>
				,public CConstantBufferContainer
			{
			protected:
				CScene * const mScene;
			public:
				CLight(ILightImp * interfaceImp);
				~CLight();
				CScene * getScene()const
				{
					return mScene;
				}

				// Inherited via TInterfaceObject
				virtual Void onMessage(ILightImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;

				// Inherited via CConstantBufferContainer
				virtual Void _updateConstantBuffer(Byte * buffer) override;
			};
		}
	}
}