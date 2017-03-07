#pragma once
#include "CommonMemoryAllocatorObjectTemplate.h"
namespace NSDevilX
{
	class CTimer
		:public TBaseObject<CTimer>
	{
	protected:
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
		long long mFrequency;
#endif
		long long mCurrentTime;
		long long mLastTime;
	public:
		static SizeT getSystemTime();
		CTimer();
		~CTimer();
		SizeT getInMillisecond();
		Void updateCurrentTime();
		Void updateLastTime();
	};
}