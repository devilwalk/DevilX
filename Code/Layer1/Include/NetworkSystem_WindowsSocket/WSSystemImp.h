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
				HANDLE mIOCompletePort;
				TResourcePtrMap<IServerImp*,CServerImp> mServers;
				TResourcePtrMap<IClientImp*,CClientImp> mClients;
				TResourcePtrMap<ILinkImp*,CLinkImp> mLinks;
				TListMT<CLinker*> mSearchedLinkers;
				TResourcePtrListMT<CLinker> mLinkers;
			public:
				CSystemImp();
				~CSystemImp();
				HANDLE getIOCompletePort()const
				{
					return mIOCompletePort;
				}
				CLinkImp * getLink(ILinkImp * link)const
				{
					return mLinks.get(link);
				}
				decltype(mLinkers) & getLinkersRef()
				{
					return mLinkers;
				}
				CLinker * createLinkerMT(SOCKET s);
				Void destroyLinker(CLinker * linker);
				Void addSearchLinkerMT(CLinker * linker);
				// Inherited via TMessageReceiver
				virtual Void onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			};
		}
	}
}