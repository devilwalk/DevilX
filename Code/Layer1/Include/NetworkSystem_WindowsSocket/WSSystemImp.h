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
				TResourcePtrMap<IServerImp*,CServerImp> mServers;
				TResourcePtrMap<IClientImp*,CClientImp> mClients;
				TResourcePtrMap<ILinkImp*,CLinkImp> mLinks;
				TResourcePtrListMT<CLinker> mSearchedLinkers;
			public:
				CSystemImp();
				~CSystemImp();
				CLinkImp * getLink(ILinkImp * link)const
				{
					return mLinks.get(link);
				}
				Void addSearchLinkerMT(CLinker * linker);
				// Inherited via TMessageReceiver
				virtual Void onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			};
		}
	}
}