#pragma once
namespace NSDevilX
{
	namespace NSNetworkSystem
	{
		class IServerImp
			:public IServer
			,public TBaseObject<IServerImp>
		{
		protected:
			const UInt16 mPort;
		public:
			IServerImp(UInt16 port);
			~IServerImp();

			// Í¨¹ý IServer ¼Ì³Ð
			virtual UInt16 getPort() const override;
			virtual Void setListener(IServerListener * listener) override;
			virtual IServerListener * getListener() const override;
		};
	}
}