#pragma once
#include "IGDCommandQueueImp.h"
#include "IGDMemoryAllocatorImp.h"
#include "IGDCommandAllocatorImp.h"
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGraphicsDriver
		{
			class IPhysicalDeviceGroupImp;
			class IDeviceImp
				:public IDevice
			{
			protected:
				IPhysicalDeviceGroupImp* const mPhysicsDeviceGroup;
				TResourcePtrVector<ICommandQueueImp> mQueues[IEnum::ECommandQueue_Max];
				IMemoryAllocatorImp* mDefaultMemoryAllocator;
			public:
				IDeviceImp(IPhysicalDeviceGroupImp* physicsDeviceGroup);
				virtual ~IDeviceImp();

				auto getPhysicalDeviceGroup()const
				{
					return mPhysicsDeviceGroup;
				}

				virtual IMemoryAllocator* getDefaultMemoryAllocator() const override;
			};
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
			namespace NSD3D
			{
				class IPhysicalDeviceGroupImp;
			}
			namespace NSD3D12
			{
				class IDeviceImp
					:public NSGraphicsDriver::IDeviceImp
					,public TMemoryAllocatorObject<IDeviceImp>
				{
				protected:
					CComPtr<ID3D12Device> mInternal;
				public:
					IDeviceImp(ID3D12Device* dev,NSD3D::IPhysicalDeviceGroupImp* physicsDeviceGroup);
					virtual ~IDeviceImp();

					ID3D12Device* getInternal()const{ return mInternal; }

					// 通过 IDeviceImp 继承
					virtual ICommandQueue* createCommandQueue(IEnum::ECommandQueue type,IPhysicalDevice* physicalDevice) override;
					virtual ICommandAllocator* createCommandAllocator(IEnum::ECommandQueue type) override;
				};
			}
			namespace NSD3D11
			{
				class IDeviceImp
					:public NSGraphicsDriver::IDeviceImp
					,public TMemoryAllocatorObject<IDeviceImp>
				{
				protected:
					CComPtr<ID3D11Device> mInternal;
				public:
					IDeviceImp(ID3D11Device* dev,NSD3D::IPhysicalDeviceGroupImp* physicsDeviceGroup);
					virtual ~IDeviceImp();

					ID3D11Device* getInternal()const
					{
						return mInternal;
					}

					// 通过 IDeviceImp 继承
					virtual ICommandQueue* createCommandQueue(IEnum::ECommandQueue type,IPhysicalDevice* physicalDevice) override;
					virtual ICommandAllocator* createCommandAllocator(IEnum::ECommandQueue type) override;
				};
			}
#endif
			namespace NSVulkan
			{
				class IPhysicalDeviceGroupImp;
				class IDeviceImp
					:public NSGraphicsDriver::IDeviceImp
					,public TMemoryAllocatorObject<IDeviceImp>
				{
				protected:
					const VkDevice mInternal;
				public:
					IDeviceImp(VkDevice dev,IPhysicalDeviceGroupImp* physicsDeviceGroup);
					virtual ~IDeviceImp();

					auto getInternal()const
					{
						return mInternal;
					}

					// 通过 IDeviceImp 继承
					virtual ICommandQueue* createCommandQueue(IEnum::ECommandQueue type,IPhysicalDevice* physicalDevice) override;
					virtual ICommandAllocator* createCommandAllocator(IEnum::ECommandQueue type) override;
				};
			}
			namespace NSOpenGL
			{
				class IDeviceImp
					:public NSGraphicsDriver::IDeviceImp
					,public ICommandQueueImp
					,public ICommandAllocatorImp
					,public ISwapChainImp
					,public TMemoryAllocatorObject<IDeviceImp>
				{
				protected:
					EGLContext mContext;
					EGLSurface mSurface;
				public:
					IDeviceImp(EGLContext context,NSGraphicsDriver::IPhysicalDeviceGroupImp* physicsDeviceGroup);
					virtual ~IDeviceImp();

					// 通过 IDeviceImp 继承
					virtual ICommandQueue* createCommandQueue(IEnum::ECommandQueue type,IPhysicalDevice* physicalDevice) override;
					virtual ICommandAllocator* createCommandAllocator(IEnum::ECommandQueue type) override;

					// 通过 IQueue 继承
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
					virtual ISwapChain* createSwapChain(HWND hwnd,const DXGI_SWAP_CHAIN_DESC1& desc,const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* fullscreenDesc=nullptr) override;
					virtual ISwapChain* createSwapChain(HWND hwnd,const VkSwapchainCreateInfoKHR& info) override;
#endif

					// 通过 ISwapChain 继承
					virtual void swapBuffers() override;
				};
			}
		}
	}
}