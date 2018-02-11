#include "Precompiler.h"
using namespace NSDevilX;

Void NSDevilX::CTimer::sleep(UInt32 milliseconds)
{
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	Sleep(milliseconds);
#elif DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_LINUX
	usleep(milliseconds);
#endif
}

NSDevilX::CTimer::CTimer()
	:mLastTime(tbb::tick_count::now())
	,mCurrentTime(tbb::tick_count::now())
{
}

NSDevilX::CTimer::~CTimer()
{}

SizeT NSDevilX::CTimer::getInMillisecond(Bool updateLastTime)
{
	if(updateLastTime)
		_updateLastTime();
	_updateCurrentTime();
	return static_cast<SizeT>((mCurrentTime-mLastTime).seconds()*1000);
}

Void NSDevilX::CTimer::_updateCurrentTime()
{
	mCurrentTime=tbb::tick_count::now();
}

Void NSDevilX::CTimer::_updateLastTime()
{
	mLastTime=mCurrentTime;
}
