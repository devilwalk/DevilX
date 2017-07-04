#pragma once
namespace NSDevilX
{
	namespace NSNetworkSystem
	{
		class ILinkListener
		{
		protected:
			virtual ~ILinkListener()
			{}
		public:
			virtual Void onDataReceived(ConstVoidPtr data,UInt32 dataSizeInBytes)=0;
		};
		class ILink
		{
		protected:
			virtual ~ILink(){}
		public:
			virtual const String & getServerIP()const=0;
			virtual UInt16 getServerPort()const=0;
			virtual const String & getClientIP()const=0;
			virtual UInt16 getClientPort()const=0;
			virtual Void addSendData(ConstVoidPtr data,UInt32 sizeInBytes)=0;
			virtual Void close()=0;
			virtual Void setListener(ILinkListener * listener)=0;
			virtual ILinkListener * getListener()const=0;
		};
	}
}