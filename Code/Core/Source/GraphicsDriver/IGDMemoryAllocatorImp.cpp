#include "../Precompiler.h"
#include "D3D12MemAlloc.cpp"
#define VMA_IMPLEMENTATION
#include "vk_mem_alloc.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSGraphicsDriver;

NSDevilX::NSCore::NSGraphicsDriver::IMemoryAllocatorImp::IMemoryAllocatorImp(IDeviceImp* dev)
	:mDevice(dev)
{
}

NSDevilX::NSCore::NSGraphicsDriver::IMemoryAllocatorImp::~IMemoryAllocatorImp()
{
}

#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS

NSDevilX::NSCore::NSGraphicsDriver::NSD3D12::IMemoryAllocatorImp::IMemoryAllocatorImp(IDeviceImp* dev,const D3D12MA::ALLOCATOR_DESC& desc)
	:NSGraphicsDriver::IMemoryAllocatorImp(dev)
	,mInternal(nullptr)
{
	D3D12MA::CreateAllocator(&desc,&mInternal);
}

NSDevilX::NSCore::NSGraphicsDriver::NSD3D12::IMemoryAllocatorImp::~IMemoryAllocatorImp()
{
	mInternal->Release();
}

IDeviceMemory* NSDevilX::NSCore::NSGraphicsDriver::NSD3D12::IMemoryAllocatorImp::createMemory(D3D12_HEAP_TYPE type,D3D12_HEAP_FLAGS flags,const D3D12_RESOURCE_ALLOCATION_INFO& info)
{
	D3D12MA::ALLOCATION_DESC allocation_desc={};
	allocation_desc.HeapType=type;
	allocation_desc.ExtraHeapFlags=flags;
	D3D12MA::Allocation* ret;
	mInternal->AllocateMemory(&allocation_desc,&info,&ret);
	return nullptr;
}

IDeviceMemory* NSDevilX::NSCore::NSGraphicsDriver::NSD3D12::IMemoryAllocatorImp::createMemory(const VkMemoryRequirements& requirements,VkMemoryPropertyFlags requiredFlags,VkMemoryPropertyFlags preferredFlags)
{
	D3D12_RESOURCE_ALLOCATION_INFO info={};
	info.Alignment=requirements.alignment;
	info.SizeInBytes=requirements.size;
	D3D12_HEAP_TYPE type=D3D12_HEAP_TYPE_DEFAULT;
	if(requiredFlags&VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
		type=D3D12_HEAP_TYPE_UPLOAD;
	if(requiredFlags&VK_MEMORY_PROPERTY_HOST_CACHED_BIT)
		type=D3D12_HEAP_TYPE_READBACK;
	return createMemory(type,D3D12_HEAP_FLAG_NONE,info);
}

NSDevilX::NSCore::NSGraphicsDriver::NSD3D::IMemoryAllocatorImp::IMemoryAllocatorImp(IDeviceImp* dev)
	:NSGraphicsDriver::IMemoryAllocatorImp(dev)
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSD3D::IMemoryAllocatorImp::~IMemoryAllocatorImp()
{
}

#endif

NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IMemoryAllocatorImp::IMemoryAllocatorImp(IDeviceImp* dev,const VmaAllocatorCreateInfo& info)
	:NSGraphicsDriver::IMemoryAllocatorImp(dev)
	,mInternal(nullptr)
{
	vmaCreateAllocator(&info,&mInternal);
}

NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IMemoryAllocatorImp::~IMemoryAllocatorImp()
{
	vmaDestroyAllocator(mInternal);
}

IDeviceMemory* NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IMemoryAllocatorImp::createMemory(D3D12_HEAP_TYPE type,D3D12_HEAP_FLAGS flags,const D3D12_RESOURCE_ALLOCATION_INFO& info)
{
	VkMemoryRequirements req={};
	req.alignment=info.Alignment;
	req.size=info.SizeInBytes;
	req.memoryTypeBits=-1;
	VkMemoryPropertyFlags req_flags=0;
	VkMemoryPropertyFlags pre_flags=0;
	switch(type)
	{
	case D3D12_HEAP_TYPE_DEFAULT:
		pre_flags=VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
		break;
	case D3D12_HEAP_TYPE_UPLOAD:
		req_flags=VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT|VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
		break;
	case D3D12_HEAP_TYPE_READBACK:
		req_flags=VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT|VK_MEMORY_PROPERTY_HOST_COHERENT_BIT|VK_MEMORY_PROPERTY_HOST_CACHED_BIT;
		break;
	}
	return createMemory(req,req_flags,pre_flags);
}

IDeviceMemory* NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IMemoryAllocatorImp::createMemory(const VkMemoryRequirements& requirements,VkMemoryPropertyFlags requiredFlags,VkMemoryPropertyFlags preferredFlags)
{
	VmaAllocationCreateInfo create_info={};
	create_info.requiredFlags=requiredFlags;
	create_info.preferredFlags=preferredFlags;
	VmaAllocation allocation=nullptr;
	VmaAllocationInfo allocation_info={};
	vmaAllocateMemory(mInternal,&requirements,&create_info,&allocation,&allocation_info);
	return nullptr;
}

NSDevilX::NSCore::NSGraphicsDriver::NSOpenGL::IMemoryAllocatorImp::IMemoryAllocatorImp(IDeviceImp* dev)
	:NSGraphicsDriver::IMemoryAllocatorImp(dev)
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSOpenGL::IMemoryAllocatorImp::~IMemoryAllocatorImp()
{
}
