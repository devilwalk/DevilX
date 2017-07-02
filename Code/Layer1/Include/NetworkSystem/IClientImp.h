#pragma once
#include "ILinkImp.h"
namespace NSDevilX
{
	namespace NSNetworkSystem
	{
		class IClientImp
			:public IClient
			,public TBaseObject<IClientImp>
		{
		protected:
			ILinkImp * const mLink;
		public:
			IClientImp(ILinkImp * link);
			~IClientImp();
		};
	}
}