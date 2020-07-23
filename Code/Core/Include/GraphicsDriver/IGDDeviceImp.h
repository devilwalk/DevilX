#pragma once
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
			public:
				IDeviceImp(IPhysicalDeviceGroupImp* physicsDeviceGroup);
				virtual ~IDeviceImp();
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

					// ͨ�� IDeviceImp �̳�
					virtual IQueue* createQueue(IEnum::EQueue type) override;
				};
			}
			namespace NSD3D11
			{
				class IDeviceImp
					:public NSGraphicsDriver::IDeviceImp
					,public IQueue
					,public TBaseObject<IDeviceImp>
				{
				protected:
					CComPtr<ID3D11Device> mInternal;
				public:
					IDeviceImp(ID3D11Device* dev,NSD3D::IPhysicalDeviceGroupImp* physicsDeviceGroup);
					virtual ~IDeviceImp();

					// ͨ�� IDeviceImp �̳�
					virtual IQueue* createQueue(IEnum::EQueue type) override;

					// ͨ�� IQueue �̳�
					virtual ISwapChain* createSwapChain(HWND hwnd,const DXGI_SWAP_CHAIN_DESC1& desc,const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* fullscreenDesc=nullptr) override;
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
					VkDevice mInternal;
				public:
					IDeviceImp(VkDevice dev,IPhysicalDeviceGroupImp* physicsDeviceGroup);
					virtual ~IDeviceImp();

					// ͨ�� IDeviceImp �̳�
					virtual IQueue* createQueue(IEnum::EQueue type) override;
				};
			}
			namespace NSOpenGL
			{
				class IDeviceImp
					:public NSGraphicsDriver::IDeviceImp
					,public IQueue
					,public ISwapChain
					,public TBaseObject<IDeviceImp>
				{
				protected:
					EGLContext mContext;
					EGLSurface mSurface;
				public:
					IDeviceImp(EGLContext context,NSGraphicsDriver::IPhysicalDeviceGroupImp* physicsDeviceGroup);
					virtual ~IDeviceImp();

					// ͨ�� IDeviceImp �̳�
					virtual IQueue* createQueue(IEnum::EQueue type) override;

					// ͨ�� IQueue �̳�
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
					virtual ISwapChain* createSwapChain(HWND hwnd,const DXGI_SWAP_CHAIN_DESC1& desc,const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* fullscreenDesc=nullptr) override;
#endif
				};
			}
		}
	}
}