#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGraphicsDriver
		{
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
				class ISwapChainImp
					:public NSGraphicsDriver::ISwapChainImp
					,public TBaseObject<ISwapChainImp>
				{
				protected:
					CComPtr<IDXGISwapChain> mInternal;
				public:
					ISwapChainImp(IQueueImp* queue,HWND wnd,const DXGI_SWAP_CHAIN_DESC1& desc,const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* fullScreenDesc=nullptr);
					virtual ~ISwapChainImp();

					// 通过 ISwapChainImp 继承
					virtual void swapBuffers() override;
				};
			}
#endif
			namespace NSVulkan
			{
				class ISwapChainImp
					:public NSGraphicsDriver::ISwapChainImp
					,public TBaseObject<ISwapChainImp>
				{
				protected:
					VkSwapchainKHR mInternal;
					VkPresentInfoKHR mPresentInfo;
				public:
					ISwapChainImp(IQueueImp* queue,const VkSwapchainCreateInfoKHR& info);
					~ISwapChainImp();

					// 通过 ISwapChainImp 继承
					virtual void swapBuffers() override;
				};
			}
		}
	}
}