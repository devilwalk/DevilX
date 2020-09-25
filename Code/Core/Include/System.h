#pragma once
#include "ITimerImp.h"
#include "GraphicsDriver/IGDSystemImp.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class CSystem
			:public TSingleton<CSystem>
		{
		protected:
			ISystem*mSystem;
			IThreadManager * mThreadManager;
			INetworkManager * mNetworkManager;
			TResourcePtrSet<ITimerImp> mTimers;
		public:
			CSystem();
			~CSystem();
			ISystem* getSystem()const
			{
				return mSystem;
			}
			IThreadManager* getThreadManager()const
			{
				return mThreadManager;
			}
			INetworkManager* getNetworkManager()const
			{
				return mNetworkManager;
			}
			auto getGraphicsDriverSystem()const
			{
				return NSGraphicsDriver::ISystemImp::getSingletonPtr();
			}
			ITimerImp * createTimer();
			Void destroyTimer(ITimerImp * timer);
		};
	}
}