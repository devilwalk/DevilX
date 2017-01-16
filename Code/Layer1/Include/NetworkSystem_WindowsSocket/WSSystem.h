#pragma once
#include "WSBaseObject.h"
#include "WSLink.h"
namespace NSDevilX
{
	namespace NSNetworkSystem
	{
		namespace NSWindowsSocket
		{
			class CSystem
				:public TBaseObject<CSystem>
				,public TMessageReceiver<ISystemImp>
				,public TSingleton<CSystem>
			{
			protected:
				SOCKET mServerSocket;
				HANDLE mServerListenThread;
				UInt16 mServerPort;
				TResourcePtrContainer<ConstVoidPtr,Void> mInstanceByInterfaceImps;
				TResourcePtrContainer<ILinkImp*,CLink> mLinks;
				TVectorMT<SOCKET> mUnprocessedSockets;
			public:
				CSystem();
				~CSystem();
				SOCKET getServerSocket()const
				{
					return mServerSocket;
				}
				UInt16 getServerPort()const
				{
					return mServerPort;
				}
				Void addUnprocessedSokcetMT(SOCKET s)
				{
					mUnprocessedSockets.pushBackMT(s);
				}
				VoidPtr getInstanceByInterfaceImp(ConstVoidPtr interfaceImp)const
				{
					return mInstanceByInterfaceImps.get(interfaceImp);
				}
				Boolean hasInstanceByInterfaceImp(ConstVoidPtr interfaceImp)const
				{
					return mInstanceByInterfaceImps.has(interfaceImp);
				}
				Void addInstanceByInterfaceImp(ConstVoidPtr interfaceImp,VoidPtr instance)
				{
					mInstanceByInterfaceImps.add(interfaceImp,instance);
				}
				Void removeInstanceByInterfaceImp(ConstVoidPtr interfaceImp)
				{
					mInstanceByInterfaceImps.erase(interfaceImp);
				}
				// Inherited via TMessageReceiver
				virtual Void onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			};
		}
	}
}