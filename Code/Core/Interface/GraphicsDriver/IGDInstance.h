#pragma once
#include "IGDPhysicalDevice.h"
#include "IGDDevice.h"
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGraphicsDriver
		{
			class IInstance
			{
			protected:
				virtual ~IInstance(){ }
			public:
				virtual IEnum::EInstanceMajorType getMajorType()const=0;
				virtual Int32 getMinorType()const=0;
				virtual UInt32 enumPhysicalDevices(IPhysicalDevice** outDevices=nullptr)=0;
				virtual UInt32 enumPhysicalDeviceGroups(IPhysicalDeviceGroup** outGroups=nullptr)=0;
				virtual IDevice* createDevice(IPhysicalDeviceGroup* deviceGroup)=0;
			};
		}
	}
}