#pragma once
#include "GLES3ConstantBufferContainer.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGLES3
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