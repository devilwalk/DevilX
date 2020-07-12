#include "../Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSGraphicsDriver;

NSDevilX::NSCore::NSGraphicsDriver::IPhysicsDeviceImp::IPhysicsDeviceImp(IPhysicsDeviceGroupImp* group)
	:mGroup(group)
{
}

NSDevilX::NSCore::NSGraphicsDriver::IPhysicsDeviceImp::~IPhysicsDeviceImp()
{
}

IPhysicsDeviceGroup* NSDevilX::NSCore::NSGraphicsDriver::IPhysicsDeviceImp::getGroup() const
{
	return mGroup;
}

#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS

NSDevilX::NSCore::NSGraphicsDriver::NSDXGI::IPhysicsDeviceImp::IPhysicsDeviceImp(UINT node,NSGraphicsDriver::IPhysicsDeviceGroupImp* group)
	:NSGraphicsDriver::IPhysicsDeviceImp(group)
	,mInternal(node)
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSDXGI::IPhysicsDeviceImp::~IPhysicsDeviceImp()
{
}

#endif

NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IPhysicsDeviceImp::IPhysicsDeviceImp(VkPhysicalDevice dev,NSGraphicsDriver::IPhysicsDeviceGroupImp* group)
	:NSGraphicsDriver::IPhysicsDeviceImp(group)
	,mInternal(dev)
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IPhysicsDeviceImp::~IPhysicsDeviceImp()
{
}
