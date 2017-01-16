#include "Precompiler.h"
using namespace NSDevilX;
namespace NSDevilX
{
	static std::list<CMemoryTracker*> gMemoryTrackerList;
	static std::mutex gMemoryTrackerListWriteLocker;
	static std::atomic<SizeT> gMemoryTrackerListReadLocker;
	static CDefaultMemoryTracker * gDefaultMemoryTracker=nullptr;
}
CMemoryTracker * NSDevilX::getMemoryTracker()
{
	CMemoryTracker * ret=0;
	ThreadID thread_id=CThreadManager::getCurrentThreadID();
	gMemoryTrackerListWriteLocker.lock();
	++gMemoryTrackerListReadLocker;
	gMemoryTrackerListWriteLocker.unlock();
	for(auto tracker:gMemoryTrackerList)
	{
		if(tracker->getThreadID()==thread_id)
		{
			ret=tracker;
			break;
		}
	}
	--gMemoryTrackerListReadLocker;
	if(!ret)
	{
		ret=new CMemoryTracker(thread_id);
		gMemoryTrackerListWriteLocker.lock();
		while(gMemoryTrackerListReadLocker);
		gMemoryTrackerList.push_back(ret);
		gMemoryTrackerListWriteLocker.unlock();
	}
	return ret;
}
CDefaultMemoryTracker * NSDevilX::getDefaultMemoryTracker()
{
	static std::mutex locker;
	locker.lock();
	if(!gDefaultMemoryTracker)
		gDefaultMemoryTracker=new CDefaultMemoryTracker();
	locker.unlock();
	return gDefaultMemoryTracker;
}
void NSDevilX::destroyMemoryTracker()
{
	gMemoryTrackerListWriteLocker.lock();
	while(gMemoryTrackerListReadLocker);
	for(auto tracker:gMemoryTrackerList)
	{
		delete tracker;
	}
	gMemoryTrackerList.clear();
	gMemoryTrackerListWriteLocker.unlock();
	delete gDefaultMemoryTracker;
	gDefaultMemoryTracker=0;
}