#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class INetworkConnection;
		class IINetworkConnectionListener
		{
		protected:
			virtual ~IINetworkConnectionListener()
			{}
		public:
			virtual void onDataReceived(const void * data,size_t sizeInBytes)=0;
			virtual void onDeconnected()=0;
		};
		class INetworkConnection
		{
		protected:
			virtual ~INetworkConnection(){}
		public:
			virtual std::string getMyIP()const=0;
			virtual unsigned short getMyPort()const=0;
			virtual std::string getEndPointIP()const=0;
			virtual unsigned short getEndPointPort()const=0;
			virtual void send(const void * data,size_t sizeInBytes)=0;
			virtual void addListener(IINetworkConnectionListener * listener)=0;
			virtual void removeListener(IINetworkConnectionListener * listener)=0;
		};
	}
}