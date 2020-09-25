#include "../Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSGraphicsDriver;

NSDevilX::NSCore::NSGraphicsDriver::ICommandAllocatorImp::ICommandAllocatorImp(IEnum::ECommandQueue queueType,IDeviceImp* device)
	:mQueueType(queueType)
	,mDevice(device)
{
}

NSDevilX::NSCore::NSGraphicsDriver::ICommandAllocatorImp::~ICommandAllocatorImp()
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSD3D12::ICommandAllocatorImp::ICommandAllocatorImp(IEnum::ECommandQueue queueType,NSD3D12::IDeviceImp* device)
	:NSGraphicsDriver::ICommandAllocatorImp(queueType,device)
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSD3D12::ICommandAllocatorImp::~ICommandAllocatorImp()
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::ICommandAllocatorImp::ICommandAllocatorImp(IEnum::ECommandQueue queueType,NSVulkan::IDeviceImp* device)
	:NSGraphicsDriver::ICommandAllocatorImp(queueType,device)
	,mInternal(VK_NULL_HANDLE)
{
	VkCommandPoolCreateInfo cmd_pool_create_info={};
	cmd_pool_create_info.sType=VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	cmd_pool_create_info.queueFamilyIndex=static_cast<IPhysicalDeviceImp*>(device->getPhysicalDeviceGroup()->getDevices()[0])->getQueueFamilies()[queueType][0].mQueueFamilyIndex;
	cmd_pool_create_info.flags=VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
	vkCreateCommandPool(device->getInternal(),&cmd_pool_create_info,nullptr,&mInternal);
}

NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::ICommandAllocatorImp::~ICommandAllocatorImp()
{
	if(VK_NULL_HANDLE!=mInternal)
	{
		vkDestroyCommandPool(static_cast<IDeviceImp*>(mDevice)->getInternal(),mInternal,nullptr);
	}
}
