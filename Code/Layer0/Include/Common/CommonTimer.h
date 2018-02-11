#pragma once
#include "CommonMemoryAllocatorObjectTemplate.h"
namespace NSDevilX
{
	class CTimer
		:public TBaseObject<CTimer>
	{
	protected:
		tbb::tick_count mCurrentTime;
		tbb::tick_count mLastTime;
	public:
		static Void sleep(UInt32 milliseconds);
		CTimer();
		~CTimer();
		SizeT getInMillisecond(Bool updateLastTime=True);
	protected:
		Void _updateCurrentTime();
		Void _updateLastTime();
	};
}