#pragma once
#include "IGDQueueImp.h"
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
				TResourcePtrVector(IQueueImp) mQueues[3];
			public:
				IDeviceImp(IPhysicalDeviceGroupImp* physicsDeviceGroup);
				virtual ~IDeviceImp();

				auto getPhysicalDeviceGroup()const
				{
					return mPhysicsDeviceGroup;
				}
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
					,public TBaseObject<IDeviceImp>
				{
				protected:
					CComPtr<ID3D12Device> mInternal;
				public:
					IDeviceImp(ID3D12Device* dev,NSD3D::IPhysicalDeviceGroupImp* physicsDeviceGroup);
					virtual ~IDeviceImp();

					// 通过 IDeviceImp 继承
					virtual UInt32 getQueueCount(IEnum::EQueue type) const override;
					virtual IQueue* getQueue(IEnum::EQueue type,UInt32 index) override;
				};
			}
			namespace NSD3D11
			{
				class IDeviceImp
					:public NSGraphicsDriver::IDeviceImp
					,public IQueueImp
					,public TBaseObject<IDeviceImp>
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
					virtual UInt32 getQueueCount(IEnum::EQueue type) const override;
					virtual IQueue* getQueue(IEnum::EQueue type,UInt32 index) override;

					// 通过 IQueue 继承
					virtual ISwapChain* createSwapChain(DXGI_SWAP_CHAIN_DESC& desc) override;
					virtual ISwapChain* createSwapChain(HWND hwnd,const DXGI_SWAP_CHAIN_DESC1& desc,const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* fullscreenDesc=nullptr) override;
					virtual ISwapChain* createSwapChain(HWND hwnd,const VkSwapchainCreateInfoKHR& info) override;
				};
			}
#endif
			namespace NSVulkan
			{
				class IPhysicalDeviceGroupImp;
				class IDeviceImp
					:public NSGraphicsDriver::IDeviceImp
					,public TBaseObject<IDeviceImp>
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
					virtual UInt32 getQueueCount(IEnum::EQueue type) const override;
					virtual IQueue* getQueue(IEnum::EQueue type,UInt32 index) override;
				};
			}
			namespace NSOpenGL
			{
				class IDeviceImp
					:public NSGraphicsDriver::IDeviceImp
					,public IQueueImp
					,public ISwapChain
					,public TBaseObject<IDeviceImp>
				{
				protected:
					EGLContext mContext;
					EGLSurface mSurface;
				public:
					IDeviceImp(EGLContext context,NSGraphicsDriver::IPhysicalDeviceGroupImp* physicsDeviceGroup);
					virtual ~IDeviceImp();

					// 通过 IDeviceImp 继承
					virtual UInt32 getQueueCount(IEnum::EQueue type) const override;
					virtual IQueue* getQueue(IEnum::EQueue type,UInt32 index) override;

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