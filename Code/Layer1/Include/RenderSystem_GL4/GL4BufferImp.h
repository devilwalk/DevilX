#pragma once
#include "GL4BufferUpdater.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGL4
		{
			class CBufferImp
				:public TBaseObject<CBufferImp>
				,public TInterfaceObject<IBufferImp>
				,public CGLInternalObject
				,public TMessageReceiver<CSystemImp>
				,public CReferenceObject
				,public CMessageNotifier
			{
			public:
				enum EMessage
				{
					EMessage_InternalCreate
				};
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