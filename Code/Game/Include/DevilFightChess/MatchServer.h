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
			struct SConnectRequest
			{
				const Byte mData[15];
				SConnectRequest()
					:mData({'D','e','v','i','l','F','i','g','h','t','C','h','e','s','s'})
				{}
			};
			struct SConnectResponse
			{
				const Byte mData[15];
				SConnectResponse()
					:mData({'D','e','v','i','l','F','i','g','h','t','C','h','e','s','s'})
				{}
			};
		protected:
			NSNetworkSystem::IServer * mServer;
			TSet<NSNetworkSystem::ILink*> mInvalidLinks;
			TList<NSNetworkSystem::ILink*> mLinks;
		public:
			CMatchServer();
			~CMatchServer();

		protected:
			Void _processProtocal(NSNetworkSystem::ILink * link,ConstVoidPtr data,UInt32 dataSizeInBytes);
			// ͨ�� IServerListener �̳�
			virtual Boolean onConnect(NSNetworkSystem::IServer * server,const String & clientIP,UInt16 clientPort) override;
			virtual Void onConnected(NSNetworkSystem::IServer * server,NSNetworkSystem::ILink * link) override;

			// ͨ�� ILinkListener �̳�
			virtual Void onDataReceived(NSNetworkSystem::ILink * link,ConstVoidPtr data,UInt32 dataSizeInBytes) override;
			virtual Void onDeconnect(NSNetworkSystem::ILink * link) override;
		};
	}
}