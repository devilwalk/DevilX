#include "../Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSGraphicsDriver;

NSDevilX::NSCore::NSGraphicsDriver::IPhysicalDeviceImp::IPhysicalDeviceImp(IPhysicalDeviceGroupImp* group)
	:mGroup(group)
{
}

NSDevilX::NSCore::NSGraphicsDriver::IPhysicalDeviceImp::~IPhysicalDeviceImp()
{
}

IPhysicalDeviceGroup* NSDevilX::NSCore::NSGraphicsDriver::IPhysicalDeviceImp::getGroup() const
{
	return mGroup;
}

NSDevilX::NSCore::NSGraphicsDriver::INonePhysicalDeviceImp::INonePhysicalDeviceImp(IPhysicalDeviceGroupImp* group)
	:NSGraphicsDriver::IPhysicalDeviceImp(group)
{
}

NSDevilX::NSCore::NSGraphicsDriver::INonePhysicalDeviceImp::~INonePhysicalDeviceImp()
{
}

#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS

NSDevilX::NSCore::NSGraphicsDriver::NSD3D12::IPhysicalDeviceImp::IPhysicalDeviceImp(UINT node,NSD3D::IPhysicalDeviceGroupImp* group)
	:NSGraphicsDriver::IPhysicalDeviceImp(group)
	,mInternal(node)
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSD3D12::IPhysicalDeviceImp::~IPhysicalDeviceImp()
{
}

#endif

NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IPhysicalDeviceImp::IPhysicalDeviceImp(VkPhysicalDevice dev,IPhysicalDeviceGroupImp* group)
	:NSGraphicsDriver::IPhysicalDeviceImp(group)
	,mInternal(dev)
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IPhysicalDeviceImp::~IPhysicalDeviceImp()
{
}
