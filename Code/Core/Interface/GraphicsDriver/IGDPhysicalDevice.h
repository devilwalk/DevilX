#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGraphicsDriver
		{
			class IPhysicalDeviceGroup;

			class IPhysicalDeviceMemoryHeap
			{
			protected:
				virtual ~IPhysicalDeviceMemoryHeap(){}
			public:
				virtual UInt32 getVkMemoryPropertyFlags()const=0;
			};

			class IPhysicalDevice
			{
			protected:
				virtual ~IPhysicalDevice(){ }
			public:
				virtual IPhysicalDeviceGroup* getGroup()const=0;
				virtual UInt32 getMemoryHeapCount()const=0;
				virtual IPhysicalDeviceMemoryHeap* getMemoryHeap(UInt32 index)const=0;
			};

			class IPhysicalDeviceGroup
			{
			protected:
				virtual ~IPhysicalDeviceGroup(){ }
			public:
				virtual UInt32 getDeviceCount()const=0;
				virtual IPhysicalDevice* getDevice(UInt32 index)const=0;
			};
		}
	}
}