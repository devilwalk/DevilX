#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGraphicsDriver
		{
			class IQueueImp
				:public IQueue
			{
			protected:
				IDeviceImp* const mDevice;
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
				};
			}
#endif
			namespace NSVulkan
			{
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