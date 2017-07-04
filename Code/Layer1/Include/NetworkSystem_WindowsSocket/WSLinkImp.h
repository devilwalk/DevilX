#pragma once
#include "WSBaseObject.h"
#include "WSLinker.h"
namespace NSDevilX
{
	namespace NSNetworkSystem
	{
		namespace NSWindowsSocket
		{
			class CLinkImp
				:public TMessageReceiver<ISystemImp>
			{
			protected:
				ILinkImp * mInterfaceImp;
				CLinker * mLinker;
			public:
				CLinkImp(ILinkImp * interfaceImp,SOCKET s);
				virtual ~CLinkImp();
				ILinkImp * getInterfaceImp()const
				{
					return mInterfaceImp;
				}
				CLinker * getLinker()const
				{
					return mLinker;
				}
				// Inherited via TMessageReceiver
				virtual Void onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			protected:
				Void _sendData();
				Void _recvData();
			};
		}
	}
}