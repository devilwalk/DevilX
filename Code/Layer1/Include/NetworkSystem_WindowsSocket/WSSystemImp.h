#pragma once
#include "WSBaseObject.h"
namespace NSDevilX
{
	namespace NSNetworkSystem
	{
		namespace NSWindowsSocket
		{
			class CSystemImp
				:public TBaseObject<CSystemImp>
				,public TMessageReceiver<ISystemImp>
				,public TSingleton<CSystemImp>
				,public CMessageNotifier
			{
			public:
				enum EMessage
				{
					EMessage_Update
				};
			protected:
				TResourcePtrMap<ConstVoidPtr,Void> mInstanceByInterfaceImps;
				TResourcePtrMap<IServerImp*,CServerImp> mServers;
				TResourcePtrMap<IClientImp*,CClientImp> mClients;
				TResourcePtrListMT<CLinker> mSearchedLinkers;
			public:
				CSystemImp();
				~CSystemImp();
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
				Void addSearchLinkerMT(CLinker * linker);
				// Inherited via TMessageReceiver
				virtual Void onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			};
		}
	}
}