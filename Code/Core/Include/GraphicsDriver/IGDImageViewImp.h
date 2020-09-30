#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGraphicsDriver
		{
			class IImageImp;
			class IImageViewImp
				:public IImageView
			{
			protected:
				IImageImp* const mImage;
			public:
				IImageViewImp(IImageImp* image);
				virtual ~IImageViewImp();
			};
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
			namespace NSD3D12
			{
				class IImageImp;
				class IImageViewImp
					:public NSGraphicsDriver::IImageViewImp
					,public TMemoryAllocatorObject<IImageViewImp>
				{
				protected:
					D3D12_CPU_DESCRIPTOR_HANDLE mRTOrDSView;
					D3D12_CPU_DESCRIPTOR_HANDLE mShaderResourceView;
				public:
					IImageViewImp(IImageImp* image);
					virtual ~IImageViewImp();
				};
			}

			namespace NSD3D11
			{
				class IImageImp;
				class IImageViewImp
					:public NSGraphicsDriver::IImageViewImp
					,public TMemoryAllocatorObject<IImageViewImp>
				{
				protected:
					CComPtr<ID3D11RenderTargetView> mRTView;
					CComPtr<ID3D11DepthStencilView> mDSView;
					CComPtr<ID3D11ShaderResourceView> mSRView;
				public:
					IImageViewImp(IImageImp* image);
					virtual ~IImageViewImp();
				};
			}
#endif
			namespace NSVulkan
			{
				class IImageImp;
				class IImageViewImp
					:public NSGraphicsDriver::IImageViewImp
					,public TMemoryAllocatorObject<IImageViewImp>
				{
				protected:
					VkImageView mInternal;
				public:
					IImageViewImp(IImageImp* image);
					virtual ~IImageViewImp();
				};
			}
		}
	}
}