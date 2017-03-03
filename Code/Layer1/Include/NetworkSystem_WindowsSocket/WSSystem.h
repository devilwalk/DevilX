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
				TResourcePtrMap<ConstVoidPtr,Void> mInstanceByInterfaceImps;
				TResourcePtrMap<ILinkImp*,CLink> mLinks;
				TResourcePtrListMT<CLinker> mUnprocessedLinkers;
				TMapMT<String,TList<UInt16> > mSearchPorts;
				TListMT<std::pair<String,UInt16> > mOnConnects;
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
				Void addLinkerMT(CLinker * linker);
				Void removeLinkerMT(CLinker * linker);
				Void addSearchPortMT(const String & ip,UInt16 port);
				// Inherited via TMessageReceiver
				virtual Void onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			};
		}
	}
}