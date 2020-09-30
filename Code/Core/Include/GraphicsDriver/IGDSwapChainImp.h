#pragma once
#include "IGDImageImp.h"
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGraphicsDriver
		{
			class ICommandQueueImp;
			class ISwapChainImp
				:public ISwapChain
			{
			protected:
				ICommandQueueImp* const mQueue;
				TResourcePtrVector<IImageImp> mBackBuffers;
			public:
				ISwapChainImp(ICommandQueueImp* queue);
				virtual ~ISwapChainImp();

				virtual ICommandQueue* getCommandQueue() const override;

				// 通过 ISwapChain 继承
				virtual UInt32 getBackBufferCount() const override;
				virtual IImage* getBackBuffer(UInt32 index) const override;
				virtual void swapBuffers() override;
			};
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
			namespace NSD3D
			{
				class ISwapChainImp
					:public NSGraphicsDriver::ISwapChainImp
				{
				protected:
					CComPtr<IDXGISwapChain> mInternal;
				public:
					ISwapChainImp(ICommandQueueImp* queue,IDXGISwapChain* v);
					virtual ~ISwapChainImp();

					// 通过 ISwapChainImp 继承
					virtual void swapBuffers() override;
				};
			}
			namespace NSD3D12
			{
				class ICommandQueueImp;
				class ISwapChainImp
					:public NSD3D::ISwapChainImp
				{
				protected:
					UINT mCurrentBufferIndex;
				public:
					ISwapChainImp(ICommandQueueImp* queue,IDXGISwapChain* v);
					virtual ~ISwapChainImp();
				};
			}
			namespace NSD3D11
			{
				class ICommandQueueImp;
				class ISwapChainImp
					:public NSD3D::ISwapChainImp
				{
				protected:
					CComPtr<IDXGISwapChain> mInternal;
				public:
					ISwapChainImp(ICommandQueueImp* queue,IDXGISwapChain* v);
					virtual ~ISwapChainImp();
				};
			}
#endif
			namespace NSVulkan
			{
				class ICommandQueueImp;
				class ISwapChainImp
					:public NSGraphicsDriver::ISwapChainImp
					,public TMemoryAllocatorObject<ISwapChainImp>
				{
				protected:
					VkSwapchainKHR mInternal;
					VkSurfaceKHR mSurface;
					VkPresentInfoKHR mPresentInfo;
					VkAcquireNextImageInfoKHR mAcquireNextImageInfo;
					uint32_t mPresentImageIndex;
					VkFence mFence;
					VkSemaphore mSemaphore;
				public:
					ISwapChainImp(ICommandQueueImp* queue,const VkSwapchainCreateInfoKHR& info);
					~ISwapChainImp();

					// 通过 ISwapChainImp 继承
					virtual void swapBuffers() override;
				};
			}
		}
	}
}