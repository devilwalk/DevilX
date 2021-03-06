#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

NSDevilX::NSCore::ISystem::~ISystem()
{
}

void NSDevilX::NSCore::ISystem::shutdown()
{
	DEVILX_DELETE(CSystem::getSingletonPtr());
}

INetworkManager * NSDevilX::NSCore::ISystem::getNetworkManager() const
{
	return CSystem::getSingleton().getNetworkManager();
}

NSGraphicsDriver::ISystem* NSDevilX::NSCore::ISystem::getGraphicsDriverSystem() const
{
	return CSystem::getSingleton().getGraphicsDriverSystem();
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
