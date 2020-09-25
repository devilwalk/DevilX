#pragma once
#include "ThreadType.h"
#include "SemaphoreGroup.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class CThreadManager
			:public TSingleton<CThreadManager>
			,public TMemoryAllocatorObject<CThreadManager>
		{
		protected:
			CSemaphorePool*mSemaphorePool;
		public:
			CThreadManager();
			~CThreadManager();
			static ThreadID getCurrentThreadID();
			static Void sleep(UInt32 timeInMilliseconds);
			CSemaphorePool*getSemaphorePool()const{ return mSemaphorePool; }
		};
	}
}
