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

NSDevilX::NSCore::NSGraphicsDriver::NSOpenGL::IMemoryAllocatorImp::IMemoryAllocatorImp(IDeviceImp* dev)
	:NSGraphicsDriver::IMemoryAllocatorImp(dev)
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSOpenGL::IMemoryAllocatorImp::~IMemoryAllocatorImp()
{
}
