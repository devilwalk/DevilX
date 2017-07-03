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

			// Í¨¹ý IClient ¼Ì³Ð
			virtual ILink * getLink() const override;
		};
	}
}