#pragma once
#include "WSLinkImp.h"
namespace NSDevilX
{
	namespace NSNetworkSystem
	{
		namespace NSWindowsSocket
		{
			class CClientImp
				:public TBaseObject<CClientImp>
				,public TMessageReceiver<CSystemImp>
			{
			protected:
				IClientImp * const mInterfaceImp;
				CLinkImp * mLink;
			public:
				CClientImp(IClientImp * interfaceImp);
				~CClientImp();
				IClientImp * getInterfaceImp()const
				{
					return mInterfaceImp;
				}
			protected:
				// Í¨¹ý TInterfaceObject ¼Ì³Ð
				virtual Void onMessage(CSystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			};
		}
	}
}