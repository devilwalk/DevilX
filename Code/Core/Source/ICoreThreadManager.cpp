#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

NSDevilX::NSCore::IThreadManager::~IThreadManager(){}

IReadWriteLock * NSDevilX::NSCore::IThreadManager::createReadWriteLock()
{
	return DEVILX_NEW IReadWriteLockImp();
}

void NSDevilX::NSCore::IThreadManager::destroyReadWriteLock(IReadWriteLock * lock)
{
	DEVILX_DELETE(static_cast<IReadWriteLockImp*>(lock));
}

ISemaphore * NSDevilX::NSCore::IThreadManager::createSemaphore()
{
	return DEVILX_NEW ISemaphoreImp();
}

void NSDevilX::NSCore::IThreadManager::destroySemaphore(ISemaphore*semaphore)
{
	DEVILX_DELETE(static_cast<ISemaphoreImp*>(semaphore));
}

IThreadPool * NSDevilX::NSCore::IThreadManager::createThreadPool()
{
	return DEVILX_NEW IThreadPoolImp();
}

void NSDevilX::NSCore::IThreadManager::destroyThreadPool(IThreadPool * pool)
{
	DEVILX_DELETE(static_cast<IThreadPoolImp*>(pool));
}

IThread * NSDevilX::NSCore::IThreadManager::createThread()
{
	return DEVILX_NEW IThreadImp;
}

void NSDevilX::NSCore::IThreadManager::destroyThread(IThread * thread)
{
	DEVILX_DELETE(static_cast<IThreadImp*>(thread));
}

void NSDevilX::NSCore::IThreadManager::sleep(unsigned int timeInMilliseconds)
{
	CThreadManager::getSingleton().sleep(timeInMilliseconds);
}
