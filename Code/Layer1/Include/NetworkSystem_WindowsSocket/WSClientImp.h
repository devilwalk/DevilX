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
			};
		}
	}
}