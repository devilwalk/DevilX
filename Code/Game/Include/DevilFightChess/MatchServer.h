#pragma once
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CMatchServer
			:public TBaseObject<CMatchServer>
			,public NSNetworkSystem::IServerListener
			,public NSNetworkSystem::ILinkListener
		{
		public:
			struct SConnectRequestAndResponse
			{
				const Byte mData[15]={'D','e','v','i','l','F','i','g','h','t','C','h','e','s','s'};
				SConnectRequestAndResponse()
				{}
			};
		protected:
			const String mName;
			String mPassword;
			NSNetworkSystem::IServer * mServer;
			TSet<NSNetworkSystem::ILink*> mInvalidLinks;
			TList<NSNetworkSystem::ILink*> mLinks;
		public:
			CMatchServer(const String & name);
			~CMatchServer();
			const String & getName()const
			{
				return mName;
			}
			Void setPassword(const String & password)
			{
				mPassword=password;
			}
			const String & getPassword()const
			{
				return mPassword;
			}
		protected:
			Void _processProtocal(NSNetworkSystem::ILink * link,ConstVoidPtr data,UInt32 dataSizeInBytes);
			// 通过 IServerListener 继承
			virtual Boolean onConnect(NSNetworkSystem::IServer * server,const String & clientIP,UInt16 clientPort) override;
			virtual Void onConnected(NSNetworkSystem::IServer * server,NSNetworkSystem::ILink * link) override;

			// 通过 ILinkListener 继承
			virtual Void onDataReceived(NSNetworkSystem::ILink * link,ConstVoidPtr data,UInt32 dataSizeInBytes) override;
			virtual Void onDeconnect(NSNetworkSystem::ILink * link) override;
		};
	}
}