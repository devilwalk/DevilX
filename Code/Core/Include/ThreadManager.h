#pragma once
#include "ThreadType.h"
#include "Singleton.h"
#include "SemaphoreGroup.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class CThreadManager
			:public TSingletonEx<CThreadManager>
			,public TMemoryAllocatorObject<CThreadManager>
		{
		protected:
			CSemaphorePool*mSemaphorePool;
		public:
			CThreadManager();
			~CThreadManager();
			ThreadID getCurrentThreadID();
			Void sleep(UInt32 timeInMilliseconds);
			CSemaphorePool*getSemaphorePool()const{ return mSemaphorePool; }
		};
	}
}
