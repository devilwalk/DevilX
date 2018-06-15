#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

NSDevilX::NSCore::IThreadManager::~IThreadManager(){}

IReadWriteLock * NSDevilX::NSCore::IThreadManager::createReadWriteLock()
{
	return new IReadWriteLockImp();
}

void NSDevilX::NSCore::IThreadManager::destroyReadWriteLock(IReadWriteLock * lock)
{
	delete static_cast<IReadWriteLockImp*>(lock);
}

ISemaphore * NSDevilX::NSCore::IThreadManager::createSemaphore()
{
	return new ISemaphoreImp();
}

void NSDevilX::NSCore::IThreadManager::destroySemaphore(ISemaphore*semaphore)
{
	delete static_cast<ISemaphoreImp*>(semaphore);
}

IThreadPool * NSDevilX::NSCore::IThreadManager::createThreadPool()
{
	return new IThreadPoolImp();
}

void NSDevilX::NSCore::IThreadManager::destroyThreadPool(IThreadPool * pool)
{
	delete static_cast<IThreadPoolImp*>(pool);
}

IThread * NSDevilX::NSCore::IThreadManager::createThread()
{
	return new IThreadImp;
}

void NSDevilX::NSCore::IThreadManager::destroyThread(IThread * thread)
{
	delete static_cast<IThreadImp*>(thread);
}

void NSDevilX::NSCore::IThreadManager::sleep(unsigned int timeInMilliseconds)
{
	CThreadManager::getSingleton().sleep(timeInMilliseconds);
}
