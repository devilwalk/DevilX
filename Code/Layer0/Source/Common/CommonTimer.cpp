#include "Precompiler.h"
using namespace NSDevilX;

Void NSDevilX::CTimer::sleep(UInt32 milliseconds)
{
	NSCore::getSystem()->getThreadManager()->sleep(milliseconds);
}

NSDevilX::CTimer::CTimer()
	:mLastTime(NSCore::getSystem()->getTimeNowInSeconds())
	,mCurrentTime(NSCore::getSystem()->getTimeNowInSeconds())
{
}

NSDevilX::CTimer::~CTimer()
{}

SizeT NSDevilX::CTimer::getInMillisecond(Bool updateLastTime)
{
	if(updateLastTime)
		_updateLastTime();
	_updateCurrentTime();
	return static_cast<SizeT>((mCurrentTime-mLastTime)*1000);
}

Void NSDevilX::CTimer::_updateCurrentTime()
{
	mCurrentTime=NSCore::getSystem()->getTimeNowInSeconds();
}

Void NSDevilX::CTimer::_updateLastTime()
{
	mLastTime=mCurrentTime;
}
