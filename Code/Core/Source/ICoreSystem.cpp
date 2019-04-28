#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

NSDevilX::NSCore::ISystem::~ISystem()
{
}

void NSDevilX::NSCore::ISystem::shutdown()
{
	DEVILX_DELETE(CSystem::getSingletonPtr());
	delete CMemoryManager::getSingletonPtr();
}

IMemoryManager * NSDevilX::NSCore::ISystem::getMemoryManager() const
{
	return CSystem::getSingleton().getMemoryManager();
}

INetworkManager * NSDevilX::NSCore::ISystem::getNetworkManager() const
{
	return CSystem::getSingleton().getNetworkManager();
}

IGAManager * NSDevilX::NSCore::ISystem::getGAManager() const
{
	return CSystem::getSingleton().getGAManager();
}

ITimer * NSDevilX::NSCore::ISystem::createTimer() const
{
	return CSystem::getSingleton().createTimer();
}

Void NSDevilX::NSCore::ISystem::destroyTimer(ITimer * timer) const
{
	CSystem::getSingleton().destroyTimer(static_cast<ITimerImp*>(timer));
}

IThreadManager * NSDevilX::NSCore::ISystem::getThreadManager() const
{
	return CSystem::getSingleton().getThreadManager();
}

DLLAPI ISystem * NSDevilX::NSCore::getSystem()
{
	if(!CSystem::getSingletonPtr())
		DEVILX_NEW CSystem;
	return CSystem::getSingleton().getSystem();
}
