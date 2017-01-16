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
			virtual UInt16 getDeviceCount()const=0;
			virtual IPhysicalDevice * getDevice(UInt16 index)const=0;
		};
	}
}