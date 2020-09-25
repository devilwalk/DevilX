#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGraphicsDriver
		{
			class IPhysicalDeviceMemoryHeapImp
				:public IPhysicalDeviceMemoryHeap
			{
			protected:
			public:
				IPhysicalDeviceMemoryHeapImp();
				virtual ~IPhysicalDeviceMemoryHeapImp();
			};
			namespace NSVulkan
			{
				class IPhysicalDeviceMemoryHeapImp
					:public NSGraphicsDriver::IPhysicalDeviceMemoryHeapImp
					,public TMemoryAllocatorObject<IPhysicalDeviceMemoryHeapImp>
				{
				public:
					struct SMemoryType
					{
						VkMemoryPropertyFlags mFlags;
						UInt32 mIndex;
						SMemoryType()
							:mFlags(0)
							,mIndex(-1)
						{}
						SMemoryType(VkMemoryPropertyFlags flags,UInt32 index)
							:mFlags(flags)
							,mIndex(index)
						{}
					};
				protected:
					const UInt32 mIndex;
					UInt32 mFlags;
					TVector<SMemoryType> mTypes;
				public:
					IPhysicalDeviceMemoryHeapImp(UInt32 index, const SMemoryType* types, UInt32 typeCount);
					~IPhysicalDeviceMemoryHeapImp();

					virtual UInt32 getVkMemoryPropertyFlags() const override;
				};
			}
		}
	}
}