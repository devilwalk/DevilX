#pragma once
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
			public:
				ISwapChainImp(ICommandQueueImp* queue);
				virtual ~ISwapChainImp();

				virtual ICommandQueue* getCommandQueue() const override;
			};
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
			namespace NSD3D12
			{
				class ICommandQueueImp;
			}
			namespace NSD3D11
			{
				class IDeviceImp;
			}
			namespace NSD3D
			{
				class ISwapChainImp
					:public NSGraphicsDriver::ISwapChainImp
					,public TMemoryAllocatorObject<ISwapChainImp>
				{
				protected:
					CComPtr<IDXGISwapChain> mInternal;
					TCOMResourcePtrVector<ID3D12Resource> mBackBuffers12;
					TCOMResourcePtrVector<ID3D11Texture2D> mBackBuffers11;

					UINT mCurrentBufferIndex12;
				public:
					ISwapChainImp(ICommandQueueImp* queue,IDXGISwapChain* v);
					virtual ~ISwapChainImp();

					// 通过 ISwapChainImp 继承
					virtual void swapBuffers() override;
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
					TVector<VkImage> mImages;
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