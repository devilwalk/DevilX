#pragma once
#include "UtilityThreadType.h"
namespace NSDevilX
{
	class CThreadManager
	{
	protected:
	public:
		CThreadManager(){}
		~CThreadManager(){}
		static ThreadID getCurrentThreadID()
		{
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
			return ::GetCurrentThreadId();
#elif DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_LINUX
            return pthread_self();
#endif
		}
	};
}
