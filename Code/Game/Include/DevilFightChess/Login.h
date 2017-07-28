#pragma once
#include "Module.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CLogin
			:public CModule
			,public TBaseObject<CLogin>
		{
		public:
		protected:
			TSharedReadData<Int32> mReturnCode;
		public:
			CLogin();
			~CLogin();
			Void doneMT(CServer::EReturnCode code);
			// Í¨¹ý CModule ¼Ì³Ð
			virtual Void start() override;
			virtual Void update() override;
			virtual Void stop() override;
		};
	}
}