#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

void NSDevilX::NSCore::ISystem::shutdown()
{
	delete CSystem::getSingletonPtr();
	ISystem::~ISystem();
	CMemoryManager::getSingleton().deallocateBytes(this);
}

IMemoryManager * NSDevilX::NSCore::ISystem::getMemoryManager() const
{
	return CSystem::getSingleton().getMemoryManager();
}

double NSDevilX::NSCore::ISystem::getTimeNowInSeconds() const
{
	return tbb::tick_count::now().resolution();
}

IThreadManager * NSDevilX::NSCore::ISystem::getThreadManager() const
{
	return CSystem::getSingleton().getThreadManager();
}

DLLAPI ISystem * NSDevilX::NSCore::getSystem()
{
	return CSystem::getSingleton().getSystem();
}
