#pragma once
namespace NSDevilX
{
	namespace NSNetworkSystem
	{
		class ISystemImp
			:public ISystem
			,public TBaseObject<ISystemImp>
			,public CMessageNotifier
			,public TSingleton<ISystemImp>
		{
		public:
			enum EMessage
			{
				EMessage_BeginCreateServer,
				EMessage_EndCreateServer,
				EMessage_BeginDestroyServer,
				EMessage_EndDestroyServer,
				EMessage_BeginCreateClient,
				EMessage_EndCreateClient,
				EMessage_BeginDestroyClient,
				EMessage_EndDestroyClient,
				EMessage_SearchServer,
				EMessage_Destruction,
				EMessage_Update
			};
		protected:
			Bool mExit;
			ISystemListener * mListener;
			TResourcePtrMap<UInt16,IServerImp> mServers;
			TNamedResourcePtrMap<IClientImp> mClients;
			TResourcePtrList<ILinkImp> mLinks;
		public:
			ISystemImp();
			~ISystemImp();
			Bool isExit()const
			{
				return mExit;
			}
			ILinkImp * createLink(const String & serverIP,UInt16 serverPort,const String & clientIP,UInt16 clientPort);
			// Inherited via ISystem
			virtual Void shutdown() override;
			virtual Void update() override;
			virtual Void searchServer(const String & serverIP,UInt16 serverPortStart=1024,UInt16 serverPortEnd=-1) override;
			virtual IServer * createServer(UInt16 port) override;
			virtual IServer * getServer(UInt16 port) const override;
			virtual Void destroyServer(IServer * server) override;
			virtual IClient * createClient(const String & destIP,UInt16 port) override;
			virtual IClient * getClient(const String & destIP,UInt16 port) const override;
			virtual Void destroyClient(IClient * client) override;
			virtual Void setListener(ISystemListener * listener) override;
			virtual ISystemListener * getListener() const override;
		};
	}
}