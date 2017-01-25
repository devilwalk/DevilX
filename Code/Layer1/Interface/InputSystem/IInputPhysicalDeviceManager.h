#pragma once
#include "IInputPhysicalDevice.h"
namespace NSDevilX
{
	namespace NSInputSystem
	{
		class IPhysicalDeviceManager
		{
		protected:
			virtual ~IPhysicalDeviceManager(){}
		public:
			virtual UInt32 getDeviceCount()const=0;
			virtual IPhysicalDevice * getDevice(UInt32 index)const=0;
		};
	}
}