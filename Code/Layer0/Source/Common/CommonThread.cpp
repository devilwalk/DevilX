#include "Precompiler.h"
using namespace NSDevilX;

namespace NSDevilX
{
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	static DWORD __stdcall threadFunction(VoidPtr parameter)
#elif DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_LINUX
	static UInt32  threadFunction(VoidPtr parameter)
#endif
	{
		CThread::ThreadFunction func=static_cast<CThread*>(parameter)->getFunction();
		VoidPtr param=static_cast<CThread*>(parameter)->getParameter();
		func(param);
		return 0;
	}
}

NSDevilX::CThread::CThread(ThreadFunction func,VoidPtr parameter)
	:mHandle(nullptr)
	,mFunction(func)
	,mParameter(parameter)
{
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	mHandle=reinterpret_cast<VoidPtr>(CreateThread(nullptr,0,threadFunction,this,0,nullptr));
#elif DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_LINUX
#error
#endif
}

NSDevilX::CThread::~CThread()
{
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	WaitForSingleObject(mHandle,INFINITE);
	CloseHandle(mHandle);
#elif DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_LINUX
#error
#endif
}
