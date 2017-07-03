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

				// ͨ�� TInterfaceObject �̳�
				virtual Void onMessage(IClientImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			};
		}
	}
}