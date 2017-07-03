#pragma once
#include "WSLinkImp.h"
namespace NSDevilX
{
	namespace NSNetworkSystem
	{
		namespace NSWindowsSocket
		{
			class CClientImp
				:public TInterfaceObject<IClientImp>
				,public TBaseObject<CClientImp>
			{
			protected:
				CLinkImp * mLink;
			public:
				CClientImp(IClientImp * interfaceImp);
				~CClientImp();

				// Í¨¹ý TInterfaceObject ¼Ì³Ð
				virtual Void onMessage(IClientImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			};
		}
	}
}