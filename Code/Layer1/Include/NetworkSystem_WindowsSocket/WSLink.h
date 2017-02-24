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
				,public TMessageReceiver<ISystemImp>
			{
			protected:
				CLinker * mLinker;
			public:
				CLink(ILinkImp * interfaceImp);
				virtual ~CLink();
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
			class CLinkTo
				:public CLink
				,public TBaseObject<CLinkTo>
			{
			public:
				CLinkTo(ILinkImp * interfaceImp);
				~CLinkTo();
				CLinker * getLinker()const
				{
					return mLinker;
				}
			};
			class CLinkFrom
				:public CLink
				,public TBaseObject<CLinkFrom>
			{
			public:
				CLinkFrom(ILinkImp * interfaceImp,CLinker * linker);
				~CLinkFrom();
			};
		}
	}
}