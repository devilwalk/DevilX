#pragma once
#include "ICoreMemoryManager.h"
#include "ICoreThreadManager.h"
#include "ICoreNetworkManager.h"
#include "ICoreGAManager.h"
#include "ICoreTimer.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class DLLAPI ISystem
			:public CUserDataContainer
		{
		protected:
			~ISystem();
		public:
			void shutdown();
			IThreadManager*getThreadManager()const;
			IMemoryManager*getMemoryManager()const;
			INetworkManager * getNetworkManager()const;
			IGAManager * getGAManager()const;
			ITimer * createTimer()const;
			Void destroyTimer(ITimer * timer)const;
		};
		DLLAPI ISystem*getSystem();
	}
}