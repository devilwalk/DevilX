#pragma once
#include "IGDPhysicalDeviceMemoryHeapImp.h"
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
				TResourcePtrVector(IPhysicalDeviceMemoryHeapImp) mMemoryHeaps;
			public:
				IPhysicalDeviceImp(IPhysicalDeviceGroupImp* group);
				virtual ~IPhysicalDeviceImp();

				// 通过 IPhysicalDeviceImp 继承
				virtual IPhysicalDeviceGroup* getGroup() const override;
				virtual UInt32 getMemoryHeapCount() const override;
				virtual IPhysicalDeviceMemoryHeap* getMemoryHeap(UInt32 index) const override;
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
					,public IPhysicalDeviceMemoryHeapImp
					,public TBaseObject<IPhysicalDeviceImp>
				{
				protected:
					const UINT mInternal;
				public:
					IPhysicalDeviceImp(UINT node,NSD3D::IPhysicalDeviceGroupImp* group);
					virtual ~IPhysicalDeviceImp();

					// 通过 IPhysicalDeviceMemoryHeapImp 继承
					virtual UInt32 getVkMemoryPropertyFlags() const override;
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