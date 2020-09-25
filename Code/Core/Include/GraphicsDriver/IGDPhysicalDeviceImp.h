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
				const UInt32 mIndex;
				TResourcePtrVector<IPhysicalDeviceMemoryHeapImp> mMemoryHeaps;
			public:
				IPhysicalDeviceImp(IPhysicalDeviceGroupImp* group,UInt32 index=0);
				virtual ~IPhysicalDeviceImp();

				// 通过 IPhysicalDeviceImp 继承
				virtual UInt32 getIndex() const override;
				virtual IPhysicalDeviceGroup* getGroup() const override;
				virtual UInt32 getMemoryHeapCount() const override;
				virtual IPhysicalDeviceMemoryHeap* getMemoryHeap(UInt32 index) const override;
			};
			class INonePhysicalDeviceImp
				:public IPhysicalDeviceImp
				,public TMemoryAllocatorObject<INonePhysicalDeviceImp>
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
					,public TMemoryAllocatorObject<IPhysicalDeviceImp>
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
					,public TMemoryAllocatorObject<IPhysicalDeviceImp>
				{
				public:
					struct SQueueFamilyInfo
						:public TMemoryAllocatorObject<SQueueFamilyInfo>
					{
						UInt32 mQueueFamilyIndex;
						UInt32 mUseCount;
						VkQueueFamilyProperties2 mProp;
						SQueueFamilyInfo()
							:mQueueFamilyIndex(-1)
							,mUseCount(0)
						{}
					};
				protected:
					const VkPhysicalDevice mInternal;
					TVector<SQueueFamilyInfo> mQueueFamilies[3];
				public:
					IPhysicalDeviceImp(VkPhysicalDevice dev,IPhysicalDeviceGroupImp* group,UInt32 index);
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