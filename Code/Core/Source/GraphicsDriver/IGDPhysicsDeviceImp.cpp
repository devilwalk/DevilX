#include "../Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSGraphicsDriver;

NSDevilX::NSCore::NSGraphicsDriver::IPhysicsDeviceImp::IPhysicsDeviceImp()
{
}

NSDevilX::NSCore::NSGraphicsDriver::IPhysicsDeviceImp::~IPhysicsDeviceImp()
{
}

#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS

NSDevilX::NSCore::NSGraphicsDriver::NSDXGI::IPhysicsDeviceImp::IPhysicsDeviceImp(IDXGIAdapter* adapter)
	:mInternal(adapter)
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSDXGI::IPhysicsDeviceImp::~IPhysicsDeviceImp()
{
}

#endif

NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IPhysicsDeviceImp::IPhysicsDeviceImp(VkPhysicalDevice dev,uint32_t groupIndex)
	:mInternal(dev)
	,mGroupIndex(groupIndex)
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IPhysicsDeviceImp::~IPhysicsDeviceImp()
{
}
