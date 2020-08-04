#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGraphicsDriver
		{
			class IQueueImp;
			class ISwapChainImp
				:public ISwapChain
			{
			protected:
				IQueueImp* const mQueue;
			public:
				ISwapChainImp(IQueueImp* queue);
				virtual ~ISwapChainImp();
			};
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
			namespace NSD3D12
			{
				class IQueueImp;
			}
			namespace NSD3D11
			{
				class IDeviceImp;
			}
			namespace NSD3D
			{
				class ISwapChainImp
					:public NSGraphicsDriver::ISwapChainImp
					,public TBaseObject<ISwapChainImp>
				{
				protected:
					CComPtr<IDXGISwapChain> mInternal;
					TCOMResourcePtrVector(ID3D12Resource) mBackBuffers12;
					TCOMResourcePtrVector(ID3D11Texture2D) mBackBuffers11;

					UINT mCurrentBufferIndex12;
				public:
					ISwapChainImp(IQueueImp* queue,IDXGISwapChain* v);
					virtual ~ISwapChainImp();

					// ͨ�� ISwapChainImp �̳�
					virtual void swapBuffers() override;
				};
			}
#endif
			namespace NSVulkan
			{
				class IQueueImp;
				class ISwapChainImp
					:public NSGraphicsDriver::ISwapChainImp
					,public TBaseObject<ISwapChainImp>
				{
				protected:
					VkSwapchainKHR mInternal;
					VkSurfaceKHR mSurface;
					VkPresentInfoKHR mPresentInfo;
					TVector(VkImage) mImages;
					VkAcquireNextImageInfoKHR mAcquireNextImageInfo;
					uint32_t mPresentImageIndex;
					VkFence mFence;
					VkSemaphore mSemaphore;
				public:
					ISwapChainImp(IQueueImp* queue,const VkSwapchainCreateInfoKHR& info);
					~ISwapChainImp();

					// ͨ�� ISwapChainImp �̳�
					virtual void swapBuffers() override;
				};
			}
		}
	}
}