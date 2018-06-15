#pragma once
#include "CommonSingleton.h"
#include "CommonThreadPool.h"
#include "CommonCommandQueue.h"
namespace NSDevilX
{
	class CCommonManager
		:public TSingletonEx<CCommonManager>
		,public TBaseObject<CCommonManager>
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