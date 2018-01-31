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
		static Void sleep(UInt32 milliseconds);
		CTimer();
		~CTimer();
		SizeT getInMillisecond(Bool updateLastTime=True);
	protected:
		Void _updateCurrentTime();
		Void _updateLastTime();
	};
}