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

UInt32 NSDevilX::NSCore::NSGraphicsDriver::IPhysicalDeviceImp::getMemoryHeapCount() const
{
	return static_cast<UInt32>(mMemoryHeaps.size());
}

IPhysicalDeviceMemoryHeap* NSDevilX::NSCore::NSGraphicsDriver::IPhysicalDeviceImp::getMemoryHeap(UInt32 index) const
{
	return mMemoryHeaps[index];
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
	mMemoryHeaps.resize(1);
	mMemoryHeaps[0]=this;
}

NSDevilX::NSCore::NSGraphicsDriver::NSD3D12::IPhysicalDeviceImp::~IPhysicalDeviceImp()
{
	mMemoryHeaps.clear();
}

UInt32 NSDevilX::NSCore::NSGraphicsDriver::NSD3D12::IPhysicalDeviceImp::getVkMemoryPropertyFlags() const
{
	return -1;
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

	VkPhysicalDeviceMemoryProperties2 mem_prop={};
	mem_prop.sType=VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_PROPERTIES_2;
	vkGetPhysicalDeviceMemoryProperties2(mInternal,&mem_prop);

	for(uint32_t heap_index=0;heap_index<mem_prop.memoryProperties.memoryHeapCount;++heap_index)
	{
		TVector(IPhysicalDeviceMemoryHeapImp::SMemoryType) mem_types;
		for(UInt32 type_index=0;type_index<mem_prop.memoryProperties.memoryTypeCount;++type_index)
		{
			if(mem_prop.memoryProperties.memoryTypes[type_index].heapIndex==heap_index)
			{
				mem_types.push_back(IPhysicalDeviceMemoryHeapImp::SMemoryType(mem_prop.memoryProperties.memoryTypes[type_index].propertyFlags,type_index));
			}
		}

		mMemoryHeaps.push_back(DEVILX_NEW IPhysicalDeviceMemoryHeapImp(heap_index,&mem_types[0],static_cast<UInt32>(mem_types.size())));
	}
}

NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IPhysicalDeviceImp::~IPhysicalDeviceImp()
{
}
