#pragma once
#include "ITimerImp.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class CSystem
			:public TSingleton<CSystem>
			,public TBaseObject<CSystem>
		{
		protected:
			ISystem*mSystem;
			IMemoryManager * mMemoryManager;
			IThreadManager * mThreadManager;
			INetworkManager * mNetworkManager;
			IGAManager* mGAManager;
			TResourcePtrSet<ITimerImp> mTimers;
		public:
			CSystem();
			~CSystem();
			ISystem*getSystem()const{ return mSystem; }
			IMemoryManager*getMemoryManager()const{ return mMemoryManager; }
			IThreadManager*getThreadManager()const{ return mThreadManager; }
			INetworkManager * getNetworkManager()const { return mNetworkManager; }
			IGAManager* getGAManager()const { return mGAManager; }
			ITimerImp * createTimer();
			Void destroyTimer(ITimerImp * timer);
		};
	}
}