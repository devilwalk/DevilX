#pragma once
#include "WSBaseObject.h"
#include "WSLinker.h"
namespace NSDevilX
{
	namespace NSNetworkSystem
	{
		namespace NSWindowsSocket
		{
			class CLink
				:public TInterfaceObject<ILinkImp>
				,public TBaseObject<CLink>
				,public TMessageReceiver<ISystemImp>
				,public TMessageReceiver<CLinker>
			{
			protected:
				CLinker * mLinker;
				HANDLE mFindConnectThread;
				TSharedReadData<UInt16> mServerPort;
			public:
				CLink(ILinkImp * interfaceImp);
				~CLink();
				CLinker * getLinker()const
				{
					return mLinker;
				}
				Void setServerPort(UInt16 port);
				Bool getServerPort()
				{
					return mServerPort;
				}
				// Inherited via TInterfaceObject
				virtual Void onMessage(ILinkImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				virtual Void onMessage(CLinker * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				// Inherited via TMessageReceiver
				virtual Void onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			protected:
				Void _sendData();
				Void _recvData();
			};
		}
	}
}