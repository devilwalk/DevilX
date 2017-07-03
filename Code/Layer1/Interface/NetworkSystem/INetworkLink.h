#pragma once
namespace NSDevilX
{
	namespace NSNetworkSystem
	{
		class ILink
		{
		protected:
			virtual ~ILink(){}
		public:
			virtual const String & getServerIP()const=0;
			virtual UInt16 getServerPort()const=0;
			virtual const String & getClientIP()const=0;
			virtual UInt16 getClientPort()const=0;
			virtual Void pushSendData(ConstVoidPtr data,UInt32 sizeInBytes)=0;
			virtual UInt32 getFirstReceiveDataSizeInBytes()const=0;
			virtual Void popReceiveData(VoidPtr data)=0;
		};
	}
}