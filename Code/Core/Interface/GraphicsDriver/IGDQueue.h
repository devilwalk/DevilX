#pragma once
#include "IGDSwapChain.h"
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGraphicsDriver
		{
			class IQueue
			{
			protected:
				virtual ~IQueue(){ }
			public:
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
				virtual ISwapChain* createSwapChain(DXGI_SWAP_CHAIN_DESC& desc)=0;
				virtual ISwapChain* createSwapChain(DXGI_SWAP_CHAIN_DESC& desc,const DXGI_FORMAT* formats,UInt32 formatCount)=0;
				virtual ISwapChain* createSwapChain(DXGI_SWAP_CHAIN_DESC* descs,UInt32 descCount)=0;
				virtual ISwapChain* createSwapChain(HWND hwnd,const DXGI_SWAP_CHAIN_DESC1& desc,const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* fullscreenDesc=nullptr)=0;
				virtual ISwapChain* createSwapChain(HWND hwnd,const DXGI_SWAP_CHAIN_DESC1& desc,const DXGI_FORMAT* formats,UInt32 formatCount,const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* fullscreenDesc=nullptr)=0;
				virtual ISwapChain* createSwapChain(HWND hwnd,const DXGI_SWAP_CHAIN_DESC1* descs,UInt32 descCount,const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* fullscreenDesc=nullptr)=0;
				virtual ISwapChain* createSwapChain(HWND hwnd,const VkSwapchainCreateInfoKHR& info)=0;
				virtual ISwapChain* createSwapChain(HWND hwnd,const VkSwapchainCreateInfoKHR& info,const VkFormat* formats,UInt32 formatCount)=0;
				virtual ISwapChain* createSwapChain(HWND hwnd,const VkSwapchainCreateInfoKHR* infos,UInt32 infoCount)=0;
#endif
			};
		}
	}
}