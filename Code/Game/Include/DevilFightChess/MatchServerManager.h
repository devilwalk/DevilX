#pragma once
#include "MatchServer.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CMatchServerManager
			:public TBaseObject<CMatchServerManager>
		{
		protected:
			TNamedResourcePtrMap<CMatchServer> mServers;
		public:
			CMatchServerManager();
			~CMatchServerManager();

			CMatchServer * createServer(const String & name);
		};
	}
}