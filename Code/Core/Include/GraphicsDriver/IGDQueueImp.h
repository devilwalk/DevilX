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

					// Í¨¹ý IQueueImp ¼Ì³Ð
					virtual ISwapChain* createSwapChain(DXGI_SWAP_CHAIN_DESC& desc) override;
					virtual ISwapChain* createSwapChain(HWND hwnd,const DXGI_SWAP_CHAIN_DESC1& desc,const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* fullscreenDesc=nullptr) override;
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
					VkQueue mInternal;
				public:
					IQueueImp(IDeviceImp* dev,VkQueue queue);
					~IQueueImp();

					auto getInternal()const
					{
						return mInternal;
					}
				};
			}
		}
	}
}