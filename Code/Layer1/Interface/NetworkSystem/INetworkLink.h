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
			virtual const String & getDestination()const=0;
			virtual UInt16 getPort()const=0;
			virtual Void pushSendData(ConstVoidPtr data,UInt32 sizeInBytes)=0;
			virtual UInt32 getFirstReceiveDataSizeInBytes()const=0;
			virtual Void popReceiveData(VoidPtr data)=0;
		};
	}
}