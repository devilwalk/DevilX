#include "Precompiler.h"
using namespace NSDevilX;

NSDevilX::CCommonManager::CCommonManager()
	:mSemaphorePool(nullptr)
	,mThreadPool(nullptr)
	,mCommandQueue(nullptr)
{
	mSemaphorePool=DEVILX_NEW CSemaphorePool();
	mThreadPool=DEVILX_NEW CThreadPool(4,mSemaphorePool);
	mCommandQueue=DEVILX_NEW CCommandQueue();
}

NSDevilX::CCommonManager::~CCommonManager()
{
	DEVILX_DELETE(mThreadPool);
	DEVILX_DELETE(mSemaphorePool);
}

Void NSDevilX::CCommonManager::initialize()
{
}

Void NSDevilX::CCommonManager::shutdown()
{
	DEVILX_DELETE(this);
}

Void NSDevilX::CCommonManager::update()
{
	mCommandQueue->update();
}
