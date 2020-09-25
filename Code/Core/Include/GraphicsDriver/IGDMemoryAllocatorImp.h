#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGraphicsDriver
		{
			class IDevilImp;
			class IMemoryAllocatorImp
				:public IMemoryAllocator
			{
			protected:
				IDeviceImp* const mDevice;
			public:
				IMemoryAllocatorImp(IDeviceImp* dev);
				virtual ~IMemoryAllocatorImp();
			};
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
			namespace NSD3D12
			{
				class IDeviceImp;
				class IMemoryAllocatorImp
					:public NSGraphicsDriver::IMemoryAllocatorImp
					,public TMemoryAllocatorObject<IMemoryAllocatorImp>
				{
				protected:
					D3D12MA::Allocator* mInternal;
				public:
					IMemoryAllocatorImp(IDeviceImp* dev,const D3D12MA::ALLOCATOR_DESC& desc);
					~IMemoryAllocatorImp();

					// 通过 IMemoryAllocatorImp 继承
					virtual IDeviceMemory* createMemory(D3D12_HEAP_TYPE type,D3D12_HEAP_FLAGS flags,const D3D12_RESOURCE_ALLOCATION_INFO& info) override;
					virtual IDeviceMemory* createMemory(const VkMemoryRequirements& requirements,VkMemoryPropertyFlags requiredFlags,VkMemoryPropertyFlags preferredFlags) override;
				};
			}
			namespace NSD3D
			{
				class IMemoryAllocatorImp
					:public NSGraphicsDriver::IMemoryAllocatorImp
					,public TMemoryAllocatorObject<IMemoryAllocatorImp>
				{
				protected:
				public:
					IMemoryAllocatorImp(IDeviceImp* dev);
					~IMemoryAllocatorImp();
				};
			}
#endif
			namespace NSVulkan
			{
				class IDeviceImp;
				class IMemoryAllocatorImp
					:public NSGraphicsDriver::IMemoryAllocatorImp
					,public TMemoryAllocatorObject<IMemoryAllocatorImp>
				{
				protected:
					VmaAllocator mInternal;
				public:
					IMemoryAllocatorImp(IDeviceImp* dev,const VmaAllocatorCreateInfo& info);
					~IMemoryAllocatorImp();

					// 通过 IMemoryAllocatorImp 继承
					virtual IDeviceMemory* createMemory(D3D12_HEAP_TYPE type,D3D12_HEAP_FLAGS flags,const D3D12_RESOURCE_ALLOCATION_INFO& info) override;
					virtual IDeviceMemory* createMemory(const VkMemoryRequirements& requirements,VkMemoryPropertyFlags requiredFlags,VkMemoryPropertyFlags preferredFlags) override;
				};
			}
			namespace NSOpenGL
			{
				class IDeviceImp;
				class IMemoryAllocatorImp
					:public NSGraphicsDriver::IMemoryAllocatorImp
					,public TMemoryAllocatorObject<IMemoryAllocatorImp>
				{
				protected:
				public:
					IMemoryAllocatorImp(IDeviceImp* dev);
					~IMemoryAllocatorImp();
				};
			}
		}
	}
}