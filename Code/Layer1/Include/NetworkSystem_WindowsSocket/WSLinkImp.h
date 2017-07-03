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
				:public TInterfaceObject<ILinkImp>
				,public TMessageReceiver<ISystemImp>
			{
			protected:
				CLinker * mLinker;
			public:
				CLinkImp(ILinkImp * interfaceImp,SOCKET s);
				virtual ~CLinkImp();
				CLinker * getLinker()const
				{
					return mLinker;
				}
				// Inherited via TInterfaceObject
				virtual Void onMessage(ILinkImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				// Inherited via TMessageReceiver
				virtual Void onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			protected:
				Void _sendData();
				Void _recvData();
			};
		}
	}
}