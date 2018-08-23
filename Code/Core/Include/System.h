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
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
			IDirectXManager * mDirectXManager;
#endif
			TResourcePtrSet<ITimerImp> mTimers;
		public:
			CSystem();
			~CSystem();
			ISystem*getSystem()const{ return mSystem; }
			IMemoryManager*getMemoryManager()const{ return mMemoryManager; }
			IThreadManager*getThreadManager()const{ return mThreadManager; }
			INetworkManager * getNetworkManager()const { return mNetworkManager; }
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
			IDirectXManager * getDirectXManager()const { return mDirectXManager; }
#endif
			ITimerImp * createTimer();
			Void destroyTimer(ITimerImp * timer);
		};
	}
}