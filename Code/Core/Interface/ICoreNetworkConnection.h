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
			virtual Void onDataReceived(ConstVoidPtr data,SizeT sizeInBytes)=0;
			virtual Void onDeconnected()=0;
		};
		class INetworkConnection
		{
		protected:
			virtual ~INetworkConnection(){}
		public:
			virtual std::string getMyIP()const=0;
			virtual UInt16 getMyPort()const=0;
			virtual std::string getEndPointIP()const=0;
			virtual UInt16 getEndPointPort()const=0;
			virtual void send(ConstVoidPtr data,SizeT sizeInBytes)=0;
			virtual void addListener(IINetworkConnectionListener * listener)=0;
			virtual void removeListener(IINetworkConnectionListener * listener)=0;
		};
	}
}