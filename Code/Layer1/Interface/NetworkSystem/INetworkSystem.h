#pragma once
#include "INetworkLink.h"
namespace NSDevilX
{
	namespace NSNetworkSystem
	{
		class ISystem
		{
		protected:
			virtual ~ISystem(){}
		public:
			virtual Void shutdown()=0;
			virtual Void update()=0;
			virtual ILink * createLink(const String & name,const String & destIP)=0;
			virtual ILink * popUnprocessedLink(const String & name)=0;
			virtual ILink * getLink(const String & name)const=0;
			virtual Void destroyLink(ILink * link)=0;
		};
		ISystem * getSystem();
	}
}