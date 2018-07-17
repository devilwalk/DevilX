#pragma once
#include "ICoreNetworkService.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class INetworkManager
		{
		protected:
			virtual ~INetworkManager(){}
		public:
			virtual INetworkService*createService()=0;
		};
	}
}