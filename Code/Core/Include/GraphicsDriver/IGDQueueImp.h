#pragma once
#include "IGDSwapChainImp.h"
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGraphicsDriver
		{
			class IDeviceImp;
			class IQueueImp
				:public IQueue
			{
			protected:
				IDeviceImp* const mDevice;
				TResourcePtrList(ISwapChainImp) mSwapChains;
			public:
				IQueueImp(IDeviceImp* dev);
				virtual ~IQueueImp();

				auto getDevice()const
				{
					return mDevice;
				}

#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
				// 通过 IQueueImp 继承
				virtual ISwapChain* createSwapChain(DXGI_SWAP_CHAIN_DESC& desc) override;
#endif
			};
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
			namespace NSD3D12
			{
				class IDeviceImp;
				class IQueueImp
					:public NSGraphicsDriver::IQueueImp
					,public TBaseObject<IQueueImp>
				{
				protected:
					CComPtr<ID3D12CommandQueue> mInternal;
				public:
					IQueueImp(IDeviceImp* dev,ID3D12CommandQueue* queue);
					~IQueueImp();

					ID3D12CommandQueue* getInternal()const
					{
						return mInternal;
					}

					virtual ISwapChain* createSwapChain(HWND hwnd,const DXGI_SWAP_CHAIN_DESC1& desc,const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* fullscreenDesc=nullptr) override;
					virtual ISwapChain* createSwapChain(HWND hwnd,const VkSwapchainCreateInfoKHR& info) override;
				};
			}
#endif
			namespace NSVulkan
			{
				class IDeviceImp;
				class IQueueImp
					:public NSGraphicsDriver::IQueueImp
					,public TBaseObject<IQueueImp>
				{
				protected:
					const VkQueue mInternal;
					const UInt32 mFamilyIndex;
				public:
					IQueueImp(IDeviceImp* dev,VkQueue queue,UInt32 familyIndex);
					~IQueueImp();

					auto getInternal()const
					{
						return mInternal;
					}

					auto getFamilyIndex()const
					{
						return mFamilyIndex;
					}

					// 通过 IQueueImp 继承
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
					virtual ISwapChain* createSwapChain(HWND hwnd,const DXGI_SWAP_CHAIN_DESC1& desc,const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* fullscreenDesc=nullptr) override;
					virtual ISwapChain* createSwapChain(HWND hwnd,const VkSwapchainCreateInfoKHR& info) override;
#endif
				};
			}
		}
	}
}