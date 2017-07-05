#pragma once
#include "ILinkImp.h"
namespace NSDevilX
{
	namespace NSNetworkSystem
	{
		class IServerImp
			:public IServer
			,public TBaseObject<IServerImp>
		{
		protected:
			UInt16 mPort;
			IServerListener * mListener;
			TList<ILinkImp*> mLinks;
		public:
			IServerImp(UInt16 port);
			~IServerImp();
			Void setPort(UInt16 port)
			{
				mPort=port;
			}
			Void addLink(ILinkImp * link);
			// Í¨¹ý IServer ¼Ì³Ð
			virtual UInt16 getPort() const override;
			virtual Void close(ILink * link) override;
			virtual Void setListener(IServerListener * listener) override;
			virtual IServerListener * getListener() const override;
		};
	}
}