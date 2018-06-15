#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

NSDevilX::NSCore::ISemaphoreImp::ISemaphoreImp()
{
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	mInternal=CreateEvent(nullptr,FALSE,FALSE,nullptr);
#elif DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_LINUX
#error("not implement!!")
#endif
}

NSDevilX::NSCore::ISemaphoreImp::~ISemaphoreImp()
{
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	CloseHandle(mInternal);
#elif DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_LINUX
#error("not implement!!")
#endif
}

void NSDevilX::NSCore::ISemaphoreImp::notify()
{
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	SetEvent(mInternal);
#elif DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_LINUX
#error("not implement!!")
#endif
}

void NSDevilX::NSCore::ISemaphoreImp::wait(unsigned int timeOut)
{
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	WaitForSingleObject(mInternal,timeOut);
#elif DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_LINUX
#error("not implement!!")
#endif
}
