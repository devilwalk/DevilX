#pragma once
#include "UtilityThreadPool.h"
namespace NSDevilX
{
	class CCommonManager
		:public TSingletonEx<CCommonManager>
		,public TMemoryAllocatorObject<CCommonManager>
	{
	protected:
		CThreadPool*mThreadPool;
		CCommandQueue*mCommandQueue;
	public:
		CCommonManager();
		~CCommonManager();

		CThreadPool * getThreadPool()const{ return mThreadPool; }
		CCommandQueue * getCommandQueue()const{ return mCommandQueue; }
		Void initialize();
		Void shutdown();
		Void update();
	};
}