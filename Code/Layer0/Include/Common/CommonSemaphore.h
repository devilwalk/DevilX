#pragma once
#include "CommonType.h"
#include "CommonMemoryAllocatorObjectTemplate.h"
#include "CommonSTLMT.h"
namespace NSDevilX
{
	class CSemaphore
		:public TBaseObject<CSemaphore>
	{
		friend class CSemaphoreGroupWait;
	protected:
		VoidPtr mInternal;
	public:
		CSemaphore();
		~CSemaphore();
		Void notify();
		Void wait();
	};
	class CSemaphorePool;
	class CSemaphoreGroupWait
		:public TBaseObject<CSemaphoreGroupWait>
	{
	protected:
		TVectorMT<CSemaphore*> mSemaphores;
	public:
		CSemaphoreGroupWait();
		~CSemaphoreGroupWait();
		Void addSemaphoreMT(CSemaphore * semaphore);
		Void waitMT();
		Void clearMT(CSemaphorePool * pool=nullptr);
	};
}