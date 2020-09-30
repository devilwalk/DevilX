#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGraphicsDriver
		{
			class IDeviceImp;
			class IImageImp
				:public IImage
			{
			protected:
				IDeviceImp* const mDevice;
			public:
				IImageImp(IDeviceImp* device);
				virtual ~IImageImp();

				auto getDevice()const{ return mDevice; }
			};

#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
			namespace NSD3D12
			{
				class IDeviceImp;
				class IImageImp
					:public NSGraphicsDriver::IImageImp
					,public TMemoryAllocatorObject<IImageImp>
				{
				protected:
					CComPtr<ID3D12Resource> mInternal;
				public:
					IImageImp(IDeviceImp* device,ID3D12Resource* resource);
					virtual ~IImageImp();

					// 通过 IImageImp 继承
					virtual IImageView* createView(const VkImageViewCreateInfo& info) override;
				};
			}

			namespace NSD3D11
			{
				class IDeviceImp;
				class IImageImp
					:public NSGraphicsDriver::IImageImp
					,public TMemoryAllocatorObject<IImageImp>
				{
				protected:
					CComPtr<ID3D11Texture2D> mInternal;
				public:
					IImageImp(IDeviceImp* device);
					IImageImp(IDeviceImp* device,ID3D11Texture2D* resource);
					virtual ~IImageImp();

					// 通过 IImageImp 继承
					virtual IImageView* createView(const VkImageViewCreateInfo& info) override;
				};
			}
#endif

			namespace NSVulkan
			{
				class IDeviceImp;
				class IImageImp
					:public NSGraphicsDriver::IImageImp
					,public TMemoryAllocatorObject<IImageImp>
				{
				protected:
					VkImage mInternal;
				public:
					IImageImp(IDeviceImp* device,VkImage resource);
					virtual ~IImageImp();

					// 通过 IImageImp 继承
					virtual IImageView* createView(const VkImageViewCreateInfo& info) override;
				};
			}

			namespace NSOpenGL
			{
				class IDeviceImp;
				class IImageImp
					:public NSGraphicsDriver::IImageImp
					,public TMemoryAllocatorObject<IImageImp>
				{
				protected:
					GLuint mInternal;
				public:
					IImageImp(IDeviceImp* device,GLuint resource);
					virtual ~IImageImp();

					// 通过 IImageImp 继承
					virtual IImageView* createView(const VkImageViewCreateInfo& info) override;
				};
			}
		}
	}
}