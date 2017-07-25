#pragma once
#include "D3D11BufferUpdater.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CSystemImp;
			class CBufferImp
				:public TInterfaceObject<IBufferImp>
				,public TCOMInternalObject<ID3D11Buffer>
				,public TBaseObject<CBufferImp>
				,public TMessageReceiver<CSystemImp>
				,public CReferenceObject
			{
			protected:
				CBufferUpdater * mBuffer;
			public:
				CBufferImp(IBufferImp * interfaceImp);

			protected:
				~CBufferImp();
				Void _update();
				// Í¨¹ý TInterfaceObject ¼Ì³Ð
				virtual Void onMessage(IBufferImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				virtual Void onMessage(CSystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			};
		}
	}
}