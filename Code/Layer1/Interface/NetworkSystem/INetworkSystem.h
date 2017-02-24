#pragma once
#include "INetworkLink.h"
namespace NSDevilX
{
	namespace NSNetworkSystem
	{
		class ISystemListener
		{
		protected:
			virtual ~ISystemListener(){}
		public:
			virtual Void onSearch(String destIP,UInt16 port)=0;
			virtual Void onConnect(const String & destIP)=0;
			virtual Void onDeconnect(const String & destIP)=0;
		};
		class ISystem
		{
		protected:
			virtual ~ISystem(){}
		public:
			virtual Void shutdown()=0;
			virtual Void update()=0;
			virtual Void search(const String & destIP,UInt16 portStart=49152,UInt16 portEnd=-1)=0;
			virtual ILink * createLink(const String & destIP,UInt16 port)=0;
			virtual ILink * getLink(const String & destIP,UInt16 port)const=0;
			virtual Void destroyLink(ILink * link)=0;
			virtual Void setListener(ISystemListener * listener)=0;
			virtual ISystemListener * getListener()const=0;
		};
		ISystem * getSystem();
	}
}