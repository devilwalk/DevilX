#include "Precompiler.h"
using namespace NSDevilX;

Void NSDevilX::CTimer::sleep(UInt32 milliseconds)
{
	NSCore::getSystem()->getThreadManager()->sleep(milliseconds);
}

NSDevilX::CTimer::CTimer()
	:mInternal(NSCore::getSystem()->createTimer())
{
}

NSDevilX::CTimer::~CTimer()
{}

SizeT NSDevilX::CTimer::getInMillisecond()
{
	return static_cast<SizeT>(mInternal->getDeltaInSecond()*1000);
}