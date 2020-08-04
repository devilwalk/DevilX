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
				// ͨ�� IQueueImp �̳�
				virtual ISwapChain* createSwapChain(DXGI_SWAP_CHAIN_DESC& desc) override;
				virtual ISwapChain* createSwapChain(DXGI_SWAP_CHAIN_DESC& desc,const DXGI_FORMAT* formats,UInt32 formatCount) override;
				virtual ISwapChain* createSwapChain(DXGI_SWAP_CHAIN_DESC* descs,UInt32 descsCount) override;
				virtual ISwapChain* createSwapChain(HWND hwnd,const DXGI_SWAP_CHAIN_DESC1& desc,const DXGI_FORMAT* formats,UInt32 formatCount,const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* fullscreenDesc=nullptr) override;
				virtual ISwapChain* createSwapChain(HWND hwnd,const DXGI_SWAP_CHAIN_DESC1* descs,UInt32 descCount,const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* fullscreenDesc=nullptr) override;
				virtual ISwapChain* createSwapChain(HWND hwnd,const VkSwapchainCreateInfoKHR& info,const VkFormat* formats,UInt32 formatCount) override;
				virtual ISwapChain* createSwapChain(HWND hwnd,const VkSwapchainCreateInfoKHR* infos,UInt32 infoCount) override;
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

					using NSGraphicsDriver::IQueueImp::createSwapChain;

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

					using NSGraphicsDriver::IQueueImp::createSwapChain;

					auto getInternal()const
					{
						return mInternal;
					}

					auto getFamilyIndex()const
					{
						return mFamilyIndex;
					}

					// ͨ�� IQueueImp �̳�
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
					virtual ISwapChain* createSwapChain(HWND hwnd,const DXGI_SWAP_CHAIN_DESC1& desc,const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* fullscreenDesc=nullptr) override;
					virtual ISwapChain* createSwapChain(HWND hwnd,const VkSwapchainCreateInfoKHR& info) override;
#endif
				};
			}
		}
	}
}