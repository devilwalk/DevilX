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
			IClientImp(const String & serverIP,UInt16 serverPort);
			~IClientImp();

			// ͨ�� IClient �̳�
			virtual ILink * getLink() const override;
		};
	}
}