#include "Precompiler.h"
using namespace NSDevilX;

SizeT NSDevilX::CTimer::getSystemTime()
{
	SizeT ret=0;
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	ret=GetTickCount();
#elif DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_LINUX
	ret=clock();
#endif
	return ret;
}

Void NSDevilX::CTimer::sleep(UInt32 milliseconds)
{
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	Sleep(milliseconds);
#elif DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_LINUX
	usleep(milliseconds);
#endif
}

NSDevilX::CTimer::CTimer()
	:mLastTime(0)
	,mCurrentTime(0)
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	,mFrequency(0)
#endif
{
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	mFrequency=frequency.QuadPart;
#endif
}

NSDevilX::CTimer::~CTimer()
{}

SizeT NSDevilX::CTimer::getInMillisecond(Bool updateLastTime)
{
	if(updateLastTime)
		_updateLastTime();
	_updateCurrentTime();
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	return static_cast<SizeT>(static_cast<double>(mCurrentTime-mLastTime)/mFrequency*1000.0);
#elif DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_LINUX
	return (mCurrentTime-mLastTime)/CLOCKS_PER_SEC;
#endif
}

Void NSDevilX::CTimer::_updateCurrentTime()
{
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	LARGE_INTEGER current_counter;
	QueryPerformanceCounter(&current_counter);
	mCurrentTime=current_counter.QuadPart;
#elif DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_LINUX
	mCurrentTime=clock();
#endif
}

Void NSDevilX::CTimer::_updateLastTime()
{
	mLastTime=mCurrentTime;
}
