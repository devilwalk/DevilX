#pragma once
#include "Module.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CRegister
			:public TBaseObject<CRegister>
			,public CModule
		{
		public:
		protected:
			TSharedReadData<Int32> mReturnCode;
		public:
			CRegister();
			~CRegister();
			Void doneMT(CServer::EReturnCode code);

			// ͨ�� CModule �̳�
			virtual Void start() override;
			virtual Void update() override;
			virtual Void stop() override;
		};
	}
}