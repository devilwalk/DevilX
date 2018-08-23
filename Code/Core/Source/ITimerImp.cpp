#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

NSDevilX::NSCore::ITimerImp::ITimerImp()
	:mInit(tbb::tick_count::now())
{
}

NSDevilX::NSCore::ITimerImp::~ITimerImp()
{
}

DoubleFloat NSDevilX::NSCore::ITimerImp::getDeltaInSecond()
{
	auto delta=tbb::tick_count::now()-mInit;
	return delta.seconds();
}
