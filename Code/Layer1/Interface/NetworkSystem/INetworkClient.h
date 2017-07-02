#pragma once
#include "INetworkLink.h"
namespace NSDevilX
{
	namespace NSNetworkSystem
	{
		class IClient
		{
		protected:
			virtual ~IClient(){}
		public:
			virtual ILink * getLink()const=0;
		};
	}
}