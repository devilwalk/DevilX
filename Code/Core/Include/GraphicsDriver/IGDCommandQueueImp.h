#pragma once
#include "IGDSwapChainImp.h"
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGraphicsDriver
		{
			class IDeviceImp;
			class ICommandQueueImp
				:public ICommandQueue
			{
			protected:
				IDeviceImp* const mDevice;
				TResourcePtrList<ISwapChainImp> mSwapChains;
			public:
				ICommandQueueImp(IDeviceImp* dev);
				virtual ~ICommandQueueImp();

				auto getDevice()const
				{
					return mDevice;
				}

#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
				// 通过 IQueueImp 继承
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
			namespace NSD3D11
			{
				class IDeviceImp;
				class ICommandQueueImp
					:public NSGraphicsDriver::ICommandQueueImp
					,public TMemoryAllocatorObject<ICommandQueueImp>
				{
				protected:
					CComPtr<ID3D11DeviceContext> mInternal;
				public:
					ICommandQueueImp(IDeviceImp* dev,ID3D11DeviceContext* context);
					~ICommandQueueImp();

					using NSGraphicsDriver::ICommandQueueImp::createSwapChain;

					ID3D11DeviceContext* getInternal()const
					{
						return mInternal;
					}

					virtual ISwapChain* createSwapChain(DXGI_SWAP_CHAIN_DESC& desc) override;
					virtual ISwapChain* createSwapChain(HWND hwnd,const DXGI_SWAP_CHAIN_DESC1& desc,const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* fullscreenDesc=nullptr) override;
					virtual ISwapChain* createSwapChain(HWND hwnd,const VkSwapchainCreateInfoKHR& info) override;
				};
			}
			namespace NSD3D12
			{
				class IDeviceImp;
				class ICommandQueueImp
					:public NSGraphicsDriver::ICommandQueueImp
					,public TMemoryAllocatorObject<ICommandQueueImp>
				{
				protected:
					CComPtr<ID3D12CommandQueue> mInternal;
				public:
					ICommandQueueImp(IDeviceImp* dev,ID3D12CommandQueue* queue);
					~ICommandQueueImp();

					using NSGraphicsDriver::ICommandQueueImp::createSwapChain;

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
				class ICommandQueueImp
					:public NSGraphicsDriver::ICommandQueueImp
					,public TMemoryAllocatorObject<ICommandQueueImp>
				{
				protected:
					VkQueue mInternal;
					const UInt32 mFamilyIndex;
					const UInt32 mQueueIndex;
				public:
					ICommandQueueImp(IDeviceImp* dev,UInt32 familyIndex,UInt32 queueIndex);
					~ICommandQueueImp();

					using NSGraphicsDriver::ICommandQueueImp::createSwapChain;

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