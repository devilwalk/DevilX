#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGraphicsDriver
		{
			class IDeviceImp;
			class ICommandAllocatorImp
				:public ICommandAllocator
			{
			protected:
				IEnum::ECommandQueue mQueueType;
				IDeviceImp* const mDevice;
			public:
				ICommandAllocatorImp(IEnum::ECommandQueue queueType,IDeviceImp* device);
				virtual ~ICommandAllocatorImp();
			};
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
			namespace NSD3D12
			{
				class IDeviceImp;
				class ICommandAllocatorImp
					:public NSGraphicsDriver::ICommandAllocatorImp
				{
				protected:
					CComPtr<ID3D12CommandAllocator> mDirect;
					CComPtr<ID3D12CommandAllocator> mBundle;
				public:
					ICommandAllocatorImp(IEnum::ECommandQueue queueType,IDeviceImp* device);
					~ICommandAllocatorImp();
				};
			}
#endif
			namespace NSVulkan
			{
				class IDeviceImp;
				class ICommandAllocatorImp
					:public NSGraphicsDriver::ICommandAllocatorImp
				{
				protected:
					VkCommandPool mInternal;
				public:
					ICommandAllocatorImp(IEnum::ECommandQueue queueType,IDeviceImp* device);
					~ICommandAllocatorImp();
				};
			}
		}
	}
}