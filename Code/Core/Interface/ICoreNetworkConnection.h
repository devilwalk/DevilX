#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class INetworkHost;
		class INetworkConnection
		{
		protected:
			virtual ~INetworkConnection(){}
		public:
			virtual Boolean isValidate()const=0;
			virtual INetworkHost * getHost()const=0;
			virtual UInt16 getHostPort()const=0;
			virtual ConstCharPtr getEndPointIP()const=0;
			virtual UInt16 getEndPointPort()const=0;
			virtual Void send(ConstVoidPtr data,SizeT sizeInBytes)=0;
			virtual ConstVoidPtr getReceivedData()const=0;
			virtual SizeT getReceivedSizeInBytes()const=0;
			virtual Void received(SizeT sizeInBytes)=0;
		};
	}
}