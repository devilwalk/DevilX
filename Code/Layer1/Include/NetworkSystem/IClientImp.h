#pragma once
#include "ILinkImp.h"
namespace NSDevilX
{
	namespace NSNetworkSystem
	{
		class IClientImp
			:public IClient
			,public TBaseObject<IClientImp>
		{
		protected:
			ILinkImp * mLink;
		public:
			IClientImp(const String & serverIP,UInt16 port);
			~IClientImp();

			// ͨ�� IClient �̳�
			virtual ILink * getLink() const override;
		};
	}
}