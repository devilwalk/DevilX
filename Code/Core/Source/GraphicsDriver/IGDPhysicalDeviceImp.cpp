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
	uint32_t num_queue_family=0;
	vkGetPhysicalDeviceQueueFamilyProperties2(mInternal,&num_queue_family,nullptr);
	if(num_queue_family)
	{
		TVector(VkQueueFamilyProperties2) props(num_queue_family);
		for(auto& prop:props)
		{
			prop.sType=VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2;
		}
		vkGetPhysicalDeviceQueueFamilyProperties2(mInternal,&num_queue_family,&props[0]);
		int and_bits[]={VK_QUEUE_GRAPHICS_BIT|VK_QUEUE_COMPUTE_BIT|VK_QUEUE_TRANSFER_BIT,VK_QUEUE_COMPUTE_BIT|VK_QUEUE_TRANSFER_BIT,VK_QUEUE_TRANSFER_BIT};
		int not_bits[]={0,VK_QUEUE_GRAPHICS_BIT,VK_QUEUE_GRAPHICS_BIT|VK_QUEUE_COMPUTE_BIT};

		for(int i=0;i<3;++i)
		{
			UInt32 family_index=0;
			for(auto& prop:props)
			{
				if(((prop.queueFamilyProperties.queueFlags&and_bits[i])==and_bits[i])
					&&(!(prop.queueFamilyProperties.queueFlags&not_bits[i])))
				{
					SQueueFamilyInfo info;
					info.mQueueFamilyIndex=family_index;
					info.mProp=prop;
					mQueueFamilies[i].push_back(info);
				}
				family_index++;
			}
		}
	}
}

NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IPhysicalDeviceImp::~IPhysicalDeviceImp()
{
}
