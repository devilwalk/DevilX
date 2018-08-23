#pragma once
namespace NSDevilX
{
	namespace NSNetworkSystem
	{
		class ILink;
		class ILinkListener
		{
		protected:
			virtual ~ILinkListener()
			{}
		public:
			virtual Void onDataReceived(ILink * link,ConstVoidPtr data,UInt32 dataSizeInBytes)=0;
			virtual Void onDeconnect(ILink * link)=0;
		};
		class IPeer;
		class ILink
		{
		protected:
			virtual ~ILink(){}
		public:
			virtual IPeer * getPeer()const=0;
			virtual const String & getRemoteIP()const=0;
			virtual UInt16 getRemotePort()const=0;
			virtual Void addSendData(ConstVoidPtr data,UInt32 sizeInBytes)=0;
			virtual Void setListener(ILinkListener * listener)=0;
			virtual ILinkListener * getListener()const=0;
		};
	}
}