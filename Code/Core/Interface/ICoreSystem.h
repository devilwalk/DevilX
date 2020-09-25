#pragma once
#include "ICoreThreadManager.h"
#include "ICoreNetworkManager.h"
#include "GraphicsDriver/IGDSystem.h"
#include "ICoreTimer.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class DLLAPI ISystem
			:public CUserDataContainer
		{
		public:
			~ISystem();
			void shutdown();
			IThreadManager* getThreadManager()const;
			INetworkManager* getNetworkManager()const;
			NSGraphicsDriver::ISystem* getGraphicsDriverSystem()const;
			ITimer * createTimer()const;
			Void destroyTimer(ITimer * timer)const;
		};
		DLLAPI ISystem*getSystem();
	}
}