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
			virtual const String & getName()const=0;
			virtual const String & getDestination()const=0;
			virtual Void pushSendData(ConstBytePtr data,UInt32 sizeInBytes)=0;
			virtual UInt32 getFirstReceiveDataSizeInBytes()const=0;
			virtual Void popReceiveData(BytePtr data)=0;
		};
	}
}