#include "Precompiler.h"
using namespace NSDevilX;

NSDevilX::CCommonManager::CCommonManager()
	:mThreadPool(nullptr)
	,mCommandQueue(nullptr)
{
	mThreadPool=DEVILX_NEW CThreadPool(4);
	mCommandQueue=DEVILX_NEW CCommandQueue();
}

NSDevilX::CCommonManager::~CCommonManager()
{
	DEVILX_DELETE(mThreadPool);
	DEVILX_DELETE(mCommandQueue);
}

Void NSDevilX::CCommonManager::initialize()
{
}

Void NSDevilX::CCommonManager::shutdown()
{
	DEVILX_DELETE(this);
	NSCore::getSystem()->shutdown();
}

Void NSDevilX::CCommonManager::update()
{
	mCommandQueue->update();
}
