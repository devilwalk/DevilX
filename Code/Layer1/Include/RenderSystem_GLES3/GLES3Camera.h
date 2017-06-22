#pragma once
#include "GLES3ConstantBufferContainer.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGLES3
		{
			class CSystemImp;
			class CCamera
				:public TInterfaceObject<ICameraImp>
				,public TBaseObject<CCamera>
				,public CConstantBufferContainer
				,public TMessageReceiver<CSystemImp>
			{
			protected:
			public:
				CCamera(ICameraImp * interfaceImp);
				~CCamera();

				// Í¨¹ý TInterfaceObject ¼Ì³Ð
				virtual Void onMessage(ICameraImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				virtual Void onMessage(CSystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				// Inherited via CConstantBufferContainer
				virtual Void _updateConstantBuffer(Byte * buffer) override;
			};
		}
	}
}