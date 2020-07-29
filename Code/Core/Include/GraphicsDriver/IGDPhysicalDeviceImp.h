#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGraphicsDriver
		{
			class IPhysicalDeviceGroupImp;
			class IPhysicalDeviceImp: public IPhysicalDevice
			{
			protected:
				IPhysicalDeviceGroupImp* const mGroup;
			public:
				IPhysicalDeviceImp(IPhysicalDeviceGroupImp* group);
				virtual ~IPhysicalDeviceImp();

				// Í¨¹ý IPhysicalDeviceImp ¼Ì³Ð
				virtual IPhysicalDeviceGroup* getGroup() const override;
			};
			class INonePhysicalDeviceImp
				:public IPhysicalDeviceImp
				,public TBaseObject<INonePhysicalDeviceImp>
			{
			public:
				INonePhysicalDeviceImp(IPhysicalDeviceGroupImp* group);
				virtual ~INonePhysicalDeviceImp();
			};
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
			namespace NSD3D
			{
				class IPhysicalDeviceGroupImp;
			}
			namespace NSD3D12
			{
				class IPhysicalDeviceImp
					:public NSGraphicsDriver::IPhysicalDeviceImp
					,public TBaseObject<IPhysicalDeviceImp>
				{
				protected:
					const UINT mInternal;
				public:
					IPhysicalDeviceImp(UINT node,NSD3D::IPhysicalDeviceGroupImp* group);
					virtual ~IPhysicalDeviceImp();
				};
			}
#endif
			namespace NSVulkan
			{
				class IPhysicalDeviceGroupImp;
				class IPhysicalDeviceImp
					:public NSGraphicsDriver::IPhysicalDeviceImp
					,public TBaseObject<IPhysicalDeviceImp>
				{
				public:
					struct SQueueFamilyInfo
					{
						UInt32 mQueueFamilyIndex;
						VkQueueFamilyProperties2 mProp;
					};
				protected:
					const VkPhysicalDevice mInternal;
					TVector(SQueueFamilyInfo) mQueueFamilies[3];
				public:
					IPhysicalDeviceImp(VkPhysicalDevice dev,IPhysicalDeviceGroupImp* group);
					virtual ~IPhysicalDeviceImp();

					auto getInternal()const
					{
						return mInternal;
					}
					auto& getQueueFamilies()const
					{
						return mQueueFamilies;
					}
				};
			}
		}
	}
}